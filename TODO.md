# TODO

## Milestones

Architecture: one FreeRTOS task per VM.
VMs are interruptible and can be executed step by step.
VMs can be cloned (shared code, private data).
Add a new CONV A, B, 0 opcode which converts value on the stack to a specified type
  This is required for correct function return types autocasting. Right now only function args are autocaasted and thus 
  are guaranteed to have a required type.

```
  function test(int $z) :int {
    // type of $z is int no matter what user passed
    return '7';
  }
```

will return a string '7', not integer.

---

### 1. Interrupt subsystem

Register PHP functions as interrupt handlers and provide event-based dispatch.

C code handles interrupts and notifies the PHP engine. The PHP engine calls the registered PHP interrupt handler.

PHP interrupts are soft interrupts, allowing arbitrary, potentially heavy code to be executed from the interrupt handler.

Supported interrupt types:

* GPIO interrupts
* PCNT interrupts
* TOUCH interrupts
* Software Timer interrupts

---

### 2. VM Yield subsystem

* Ability to pause and resume any VM regardless of its current state
* Ability to execute a VM for a given number of opcodes

---

### 3. ESP-IDF bindings

Implement a selected subset of ESP-IDF APIs, starting with the GPIO API.

Implement raw access to MMIO registers.

WiFi bindings, both native and hosted.

---

### 4. Arduino Core bindings and SLAC ("Standard Library of Arduino Classes")

An analogue of the Arduino Core `.cpp` library, implemented in PHP wherever possible.

Standard Arduino Core classes:

* `HardwareSerial`
* `SPI`
* `FS`
* `Print`
* `Server`
* etc.

So far, `Print`, `Stream`, `Server`, and `Client` have been implemented.

---

## Smaller tasks

### 1. UNIX-like `fork()` instead of the FreeRTOS Task API

Start a new VM by cloning the current VM.

```php
$pid = fork();

if ($pid == 0) {
    echo 'Child running!';
} else {
    echo 'Child has been spawned, pid=' . $pid;
}
```

Start a service from P2HP:

```php
$error = php_service_start('Service Name'); // can be called multiple times
php_service_stop('Service Name');           // only once
```

---

### 2. IPC instead of the FreeRTOS Task Notification API

Allow VMs to communicate with each other.
The main use case is communication with PHP services (standalone background PHP processes).

Implement VM-to-VM IPC using FreeRTOS queues.
Use FreeRTOS Task Notifications for lightweight VM wake/sleep synchronization.

VM#1:

```php
php_ipc_announce('My Fancy Name');
```

VM#2:

```php
$handle = php_ipc_bind(
    $announced_name,
    $auth_creds_or_null,
    $timeout
); // returns the real FreeRTOS task/VM handle as a ph7_value

$err = php_ipc_send($handle, $value); // send an arbitrary PHP value
$value = php_ipc_recv($handle, $timeout);

php_ipc_wake($handle, $value); // send a 32-bit scalar to wake up a sleeping VM
php_ipc_sleep($handle, $mask); // sleep until woken up by another VM
                                  // ($value & $mask != 0 => wake up)
```

---

### 3. `mixed` type

Done
---

### 4. `enum`

Add the `enum` keyword.

Done. No casting tho

```php
//Example
//
enum Suit :mixed
{
    case Hearts;                // 0
    case Diamonds = 99;         // 99
    case Clubs;                 // 1
    case Spades;                // 2
    case Huh = 6.7;             // 6.7 a floating point number
    case Huh2 = 'A string';     // 'A string'
}

function do_stuff(Suit $s)
{
    // ...
}

do_stuff(Suit::Spades);
```

---

### 5. `match` keyword

---

### 6. Short array syntax

Support:

```php
$arr = [];
```

`lex.c` and `compile.c` must be updated.

---

### 7. `function_exists()`

Implement `function_exists()`.

###8. empty strings are === null which is wrong.
Done


###9. Function return arguments
Done
Syntax is accepted. Compiler checks for returns from void functions and checks if nothing is returned from a function that should return a value
NO RETURN TYPECASTING is performed!

