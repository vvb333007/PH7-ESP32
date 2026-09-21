/* AI-GENERATED SIMPLE TEST TO VERIFY SLRE PATCHES, PL CO<PILATION AND GENERAL FUNCTIONS 
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/regexp.h"
#include "../src/regexp.c"
//#include "slre.h"

typedef struct {
  int n;
  pl_span sp[16];
  pl_match last;
} coll;

static int collect(const pl_match *m, void *ud) {
  coll *c = (coll *) ud;
  if (c->n < 16) c->sp[c->n] = m->g[0];
  c->n++;
  c->last = *m;
  return 0;
}

static pl_regex *comp(const char *pat, int flags) {
  int err;
  pl_regex *re = pl_compile(pat, flags, &err);
  if (!re) {
    printf("compile('%s') failed: %d\n", pat, err);
    exit(1);
  }
  return re;
}

static int comp_err(const char *pat) {
  int err = 0;
  pl_regex *re = pl_compile(pat, 0, &err);
  pl_free(re);
  return err;
}

static int check_repl(const char *pat, const char *subj, const char *tmpl, int limit,
                      const char *expect) {
  pl_regex *re = comp(pat, 0);
  int n;
  char *r = pl_replace(re, subj, (int) strlen(subj), tmpl, limit, &n);
  int ok = r && strcmp(r, expect) == 0 && n == (int) strlen(expect);
  if (!ok) printf("FAIL replace '%s' on '%s': got '%s', expected '%s'\n", pat, subj, r ? r : "(null)", expect);
  free(r);
  pl_free(re);
  return ok;
}

#define CHECK(cond) do { if (!(cond)) { printf("FAIL line %d: %s\n", __LINE__, #cond); fails++; } } while (0)

int main(void) {
  int fails = 0;
  coll c;
  pl_regex *re;
  const char *s;

  /* match_all: simple */
  re = comp("\\d+", 0);
  s = "a12b345c6";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 3);
  CHECK(c.sp[0].start == 1 && c.sp[0].end == 3);
  CHECK(c.sp[1].start == 4 && c.sp[1].end == 7);
  CHECK(c.sp[2].start == 8 && c.sp[2].end == 9);
  pl_free(re);

  /* groups + \w translation + escaped dot */
  re = comp("(\\w+)@(\\w+)\\.com", 0);
  s = "mail: foo@bar.com!";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.last.ngroups == 2);
  CHECK(c.last.g[0].start == 6 && c.last.g[0].end == 17);
  CHECK(c.last.g[1].start == 6 && c.last.g[1].end == 9);
  CHECK(c.last.g[2].start == 10 && c.last.g[2].end == 13);
  pl_free(re);

  /* non-capturing group is hidden, capture numbering stays PCRE-like */
  re = comp("(?:ab|cd)(\\d+)", 0);
  s = "xcd42x";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.last.ngroups == 1);
  CHECK(c.last.g[0].start == 1 && c.last.g[0].end == 5);
  CHECK(c.last.g[1].start == 3 && c.last.g[1].end == 5);
  pl_free(re);

  /* quantified group as the LAST group is fine */
  re = comp("(\\w+)@(\\w+)(\\.\\w+)*", 0);
  s = "u@h.example.org";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.last.g[3].start == 11 && c.last.g[3].end == 15); /* last iteration: ".org" */
  pl_free(re);

  /* nested groups when the outer one is the first group */
  re = comp("((\\d+)\\.(\\d+))", 0);
  s = "v 12.345";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.last.ngroups == 3);
  CHECK(c.last.g[1].start == 2 && c.last.g[1].end == 8);
  CHECK(c.last.g[2].start == 2 && c.last.g[2].end == 4);
  CHECK(c.last.g[3].start == 5 && c.last.g[3].end == 8);
  pl_free(re);

  /* optional group that does not take part: no stale capture from the failed attempt at 0 */
  re = comp("(a)?b", 0);
  s = "a b";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.last.g[0].start == 2 && c.last.g[0].end == 3);
  CHECK(c.last.g[1].start == -1 && c.last.g[1].end == -1);
  pl_free(re);

  /* characters that SLRE treats specially inside [...] */
  re = comp("[.]", 0);
  CHECK(pl_exec(re, "x", 1, 0, NULL) == PL_NO_MATCH);
  CHECK(pl_exec(re, "a.b", 3, 0, NULL) == PL_OK);
  pl_free(re);
  re = comp("[$]", 0);
  CHECK(pl_exec(re, "cost: $5", 8, 0, NULL) == PL_OK);
  pl_free(re);
  re = comp("[|,]", 0);
  CHECK(pl_exec(re, "a|b", 3, 0, NULL) == PL_OK);
  CHECK(pl_exec(re, "ab", 2, 0, NULL) == PL_NO_MATCH);
  pl_free(re);
  re = comp("[^.|]+", 0);
  memset(&c, 0, sizeof c);
  s = "ab.cd|e";
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 3);
  pl_free(re);

  /* {n,m}: greedy, 4 digits -> 3 + leftover 1 (no match) */
  re = comp("\\d{2,3}", 0);
  s = "1 22 333 4444";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 3);
  CHECK(c.sp[2].start == 9 && c.sp[2].end == 12);
  pl_free(re);

  /* {n}, {n,}, {0,1} on a hidden group; capture after the expansion keeps its index */
  re = comp("(?:ab){2}(c)", 0);
  s = "ababc";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.last.g[1].start == 4 && c.last.g[1].end == 5);
  pl_free(re);
  re = comp("a{2,}", 0);
  s = "a aa aaaa";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 2);
  CHECK(c.sp[1].start == 5 && c.sp[1].end == 9);
  pl_free(re);

  /* anchors: ^ only at subject start, even when searching from an offset */
  re = comp("^ab", 0);
  s = "abab";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.sp[0].start == 0 && c.sp[0].end == 2);
  pl_free(re);
  re = comp("ab$", 0);
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.sp[0].start == 2 && c.sp[0].end == 4);
  pl_free(re);

  /* case-insensitive via flag and via (?i) */
  re = comp("hello", PL_ICASE);
  CHECK(pl_exec(re, "Say HELLO", 9, 0, NULL) == PL_OK);
  pl_free(re);
  re = comp("(?i)hello", 0);
  CHECK(pl_exec(re, "Say HELLO", 9, 0, NULL) == PL_OK);
  pl_free(re);

  /* character classes */
  re = comp("[\\w.-]+@x", 0);
  s = "a.b-c_d@x";
  memset(&c, 0, sizeof c);
  CHECK(pl_match_all(re, s, (int) strlen(s), collect, &c) == 1);
  CHECK(c.sp[0].start == 0 && c.sp[0].end == 9);
  pl_free(re);

  /* '.' does not cross newlines */
  re = comp("a.b", 0);
  CHECK(pl_exec(re, "a\nb", 3, 0, NULL) == PL_NO_MATCH);
  CHECK(pl_exec(re, "axb", 3, 0, NULL) == PL_OK);
  pl_free(re);

  /* replace */
  CHECK(check_repl("(\\w+)@(\\w+)", "foo@bar baz@qux", "$2 at $1", 0, "bar at foo qux at baz"));
  CHECK(check_repl("(\\w+)@(\\w+)", "foo@bar baz@qux", "\\2/\\1", 1, "bar/foo baz@qux"));
  CHECK(check_repl("(\\d)", "a1b2", "<${1}0>", 0, "a<10>b<20>"));
  CHECK(check_repl("\\d+", "a1b22", "$$", 0, "a$b$"));
  CHECK(check_repl("x*", "abc", "-", 0, "-a-b-c-"));      /* same as Perl/PCRE */
  CHECK(check_repl("a*", "baaac", "-", 0, "-b--c-"));     /* PCRE: "-b--c-" */
  CHECK(check_repl("\\d+", "no digits", "X", 0, "no digits"));
  CHECK(check_repl("(a)|b", "b", "[$1]", 0, "[]"));       /* unset group -> empty */

  /* split */
  {
    pl_span sp[8];
    int n;
    re = comp(",\\s*", 0);
    s = "a, b,c";
    n = pl_split(re, s, (int) strlen(s), sp, 8);
    CHECK(n == 3);
    CHECK(sp[0].start == 0 && sp[0].end == 1);
    CHECK(sp[1].start == 3 && sp[1].end == 4);
    CHECK(sp[2].start == 5 && sp[2].end == 6);
    CHECK(pl_split(re, "none", 4, NULL, 0) == 1);
    pl_free(re);
  }

  /* unsupported / invalid constructs are rejected at compile time */
  CHECK(comp_err("\\bfoo") == PL_E_UNSUPPORTED);
  CHECK(comp_err("(?=x)") == PL_E_UNSUPPORTED);
  CHECK(comp_err("(a)\\1") == PL_E_UNSUPPORTED);
  CHECK(comp_err("(a){2}") == PL_E_UNSUPPORTED);
  CHECK(comp_err("^a|b") == PL_E_UNSUPPORTED);
  CHECK(comp_err("()") == PL_E_UNSUPPORTED);
  CHECK(comp_err("[\\x41-Z]") == PL_E_UNSUPPORTED);
  /* group layouts that stock SLRE numbers wrongly */
#ifndef PL_SLRE_PATCHED
  CHECK(comp_err("(a)?(b)") == PL_E_GROUPS);
  CHECK(comp_err("(a)|(b)") == PL_E_GROUPS);
  CHECK(comp_err("((a)b)(c)") == PL_E_GROUPS);
  CHECK(comp_err("(?:ab)+(c)") == PL_E_GROUPS);
  CHECK(comp_err("(?:ab){1,3}(c)") == PL_E_GROUPS);
  CHECK(comp_err("(x)((a)b)") == PL_E_GROUPS);
#else
  /* patched SLRE: the same patterns work */
  re = comp("(a)?(b)", 0);
  CHECK(pl_exec(re, "b", 1, 0, &c.last) == PL_OK && c.last.g[1].start == -1 && c.last.g[2].start == 0);
  pl_free(re);
  re = comp("(a)|(b)", 0);
  CHECK(pl_exec(re, "xb", 2, 0, &c.last) == PL_OK && c.last.g[1].start == -1 && c.last.g[2].start == 1);
  pl_free(re);
  re = comp("((a)b)(c)", 0);
  CHECK(pl_exec(re, "abc", 3, 0, &c.last) == PL_OK && c.last.g[1].end == 2 && c.last.g[2].end == 1 && c.last.g[3].start == 2);
  pl_free(re);
  re = comp("(?:ab)+(c)", 0);
  CHECK(pl_exec(re, "xababc", 6, 0, &c.last) == PL_OK && c.last.g[0].start == 1 && c.last.g[1].start == 5);
  pl_free(re);
  re = comp("a?ab", 0); /* '?' backtracks */
  CHECK(pl_exec(re, "ab", 2, 0, &c.last) == PL_OK);
  pl_free(re);
  re = comp("([ab]*)aa", 0); /* group gives characters back to the rest of the pattern */
  CHECK(pl_exec(re, "baaaa", 5, 0, &c.last) == PL_OK && c.last.g[1].end == 3);
  pl_free(re);
  re = comp("a*|b", 0); /* empty match in the first branch is a match (leftmost-first) */
  CHECK(pl_exec(re, "b", 1, 0, &c.last) == PL_OK && c.last.g[0].end == 0);
  pl_free(re);
#endif
  CHECK(comp_err("(?:a|b)(c)(d)") == PL_OK);
  CHECK(comp_err("a*+") == PL_E_UNSUPPORTED);
  CHECK(comp_err("a|^b") == PL_E_UNSUPPORTED);
  CHECK(comp_err("[[:alpha:]]") == PL_E_UNSUPPORTED);
  CHECK(comp_err("(ab") == PL_E_SYNTAX);
  CHECK(comp_err("ab)") == PL_E_SYNTAX);
  CHECK(comp_err("*a") == PL_E_SYNTAX);
  CHECK(comp_err("") == PL_E_SYNTAX);
  CHECK(comp_err("a{1001}") == PL_E_LIMITS);
  CHECK(comp_err("a{,3}") == PL_OK); /* literal "{,3}" like in PCRE */

  /* show a few translations */
  {
    const char *pats[] = {"^(\\w+)\\s*=\\s*(\\d{1,3})$", "(?:ab){2,3}c", "[^\\s,]+", "a.b\\.c"};
    size_t i;
    for (i = 0; i < sizeof pats / sizeof *pats; i++) {
      pl_regex *r = comp(pats[i], 0);
      printf("%-28s -> %s\n", pats[i], pl_slre_pattern(r));
      pl_free(r);
    }
  }

  printf(fails ? "\n%d FAILED\n" : "\nall tests passed\n", fails);
  return fails != 0;
}
