#pragma once

#define PL_SLRE_PATCHED 1       /* do not change. SLRE library variant (patched or not) */
#define PL_SLRE_FIXED_GROUPS 1


#define PL_MAX_GROUPS   31 /* max user-visible capture groups */


/* pl_match() etc failure codes 
 * slre_match() failure codes 
 */
enum {
  PL_OK = 0,
  PL_NO_MATCH = -1,
  PL_E_UNSUPPORTED = -100, /* construct SLRE cannot express: lookaround, \b, backrefs, ... */
  PL_E_SYNTAX = -101,
  PL_E_NOMEM = -102,
  PL_E_LIMITS = -103, /* too many groups / repeat count or pattern too large */
  PL_E_ENGINE = -104, /* SLRE itself reported an error while matching */
  PL_E_GROUPS = -105, /* SLRE would mis-number these groups: nested / quantified / alternated
                         groups followed by other groups, e.g. (a)?(b)  (a)|(b)  ((a)b)(c) */

  SLRE_NO_MATCH = PL_NO_MATCH,
  SLRE_UNEXPECTED_QUANTIFIER = -2,
  SLRE_UNBALANCED_BRACKETS = -3,
  SLRE_INTERNAL_ERROR = -4,
  SLRE_INVALID_CHARACTER_SET = -5,
  SLRE_INVALID_METACHARACTER = -6,
  SLRE_CAPS_ARRAY_TOO_SMALL = -7,
  SLRE_TOO_MANY_BRANCHES = -8,
  SLRE_TOO_MANY_BRACKETS = -9,
};

/* PL / SLRE flags */
enum {
  PL_ICASE = 1,                 /* Ignore case */
  SLRE_IGNORE_CASE = PL_ICASE,
};


typedef struct pl_regex pl_regex; /* opaque */

typedef struct {
  int start, end; /* byte offsets into the subject; -1/-1 if the group did not participate */
} pl_span;

/* Captures for PL */
typedef struct {
  int ngroups;                /* number of capture groups in the pattern */
  pl_span g[PL_MAX_GROUPS + 1]; /* g[0] = whole match, g[1..ngroups] = groups */
} pl_match;

/* Captures for SLRE */
struct slre_cap {
  const char * ptr;
  int len;
};

/* Matcher callback type, for PL
*/
typedef int (*pl_each_fn)(const pl_match *m, void *userdata);


/* Compile.
 * Returns NULL on error and stores the PL_E_* code in *err (err may be NULL)
 */
pl_regex *pl_compile( const char *pattern,
                      int flags,  /* So far only 1 flag is supported : ignore case*/
                      int *err);

/* Release the compiled regexp
*/
void pl_free(pl_regex *re);


/* Search for the leftmost match starting at offset `start` (like pcre_exec).
 * '^' still means "start of the whole subject", not "start offset".
 * Returns PL_OK, PL_NO_MATCH or a negative PL_E_* code.
 */
int pl_exec(const pl_regex *re,
            const char *s,
            int len,
            int start,
            pl_match *m
            );

/* Iterate over all non-overlapping matches. `fn` is called for each match;
 * if it returns non-zero the iteration stops. `fn` may be NULL (just count).
 * Returns the number of matches, or a negative PL_E_* code.
 */
int pl_match_all( const pl_regex *re,
                  const char *s,
                  int len,
                  pl_each_fn fn,
                  void *userdata
                );

/* Replace matches with a template. Template syntax:
 *   $0..$99, ${N}, \0..\99  - whole match / group N (unset group -> empty) TODO: real max is 31, see .h file
 *   $$  and  \\             - literal '$' and '\'
 * limit: max number of replacements, 0 = all.
 * Returns a malloc()ed NUL-terminated string (must be free()ed) and stores its length in
 * *out_len (NULL is ok). On failure returns NULL and, if out_len != NULL,
 * stores a negative PL_E_* code in *out_len.
 */
char *pl_replace( const pl_regex *re,
                  const char *s, 
                  int len,
                  const char *tmpl,
                  int limit,
                  int *out_len
                 );

/*
 * Split the subject on matches. Empty matches never split.
 * Writes up to max_out pieces to out (out may be NULL) and returns the TOTAL
 * number of pieces (may be > max_out), or a negative PL_E_* code.
 */
int pl_split( const pl_regex *re,
              const char *s,
              int len,
              pl_span *out,
              int max_out
             );


/* The translated pattern that is actually handed to SLRE (for debugging).
*/
const char *pl_slre_pattern(const pl_regex *re);


/* Native PH7 lightweright regex engine, only 1 function:
 */
int slre_match( const char * regexp,
                const char * buf,
                int buf_len,
                struct slre_cap * caps,
                int num_caps,
                int flags
              );
