#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "espshell.h"
#include "ph7.h"



/*
 * Когда виртуальная машина выводит что-либо (вызывая, echo или printf ), весь ее вывод попадает в эту функцию.
 * Все, что делает эта функция - перенаправляет весь вход на экран (на stdout)
 */
static int output_callback(const void *pOutput,unsigned int nOutputLen,void *pUserData /* Unused */) {

  ssize_t nWr;

  nWr = write(1,pOutput,nOutputLen);
  if( nWr < 0 )
    return PH7_ABORT;
  
  return PH7_OK;
}


/* Запустить PHP скрипт с таким-то именем. Скрипты должны быть расположены на смонтированной файловой 
 * системе TARFS, т.к. другие файловые системы не поддерживают вызов mmap(), которые необходим для работы PH7
 */
int engine_test(const char *path) {

  
  ph7 *pEngine; /* PH7 engine */
  ph7_vm *pVm;  /* Compiled PHP program */
  int rc;

  rc = ph7_init(&pEngine);

  if( rc != PH7_OK ){
    Serial.printf("Error while allocating a new PH7 engine instance\r\n");
    return -1;
  }

  ph7_config(pEngine,PH7_CONFIG_ERR_OUTPUT, output_callback, 0); // Ошибки - на экран
  ph7_config(pEngine,PH7_VM_CONFIG_TEMPDIR,"/ffat/tmp" );

  // Можно компилировать файлики. Можно сразу несколько скомпилировать и исполнять их по надобности
  // На одной Engine может висеть несколько виртуальных машин
  rc = ph7_compile_file(pEngine, path , &pVm, 0);

  if( rc == PH7_OK ) { 

    // сообщения - на экран
    rc = ph7_vm_config(pVm, PH7_VM_CONFIG_OUTPUT, output_callback, 0 );

    // Запустили скомпилированный код
    ph7_vm_exec(pVm,0);

    // Позакрывали все
    ph7_vm_release(pVm);
    ph7_release(pEngine);

    return 0;
  }

  return -1;
}

/* Добавим пользовательскую команду в шелл: "misc ИМЯ_ФАЙЛА", для исполнения выбранных файлов
 *
 */
SHELL_USER_HANDLER(argc, argv);
SHELL_USER_HANDLER(argc, argv) {

  
  if (argc > 1) {
      engine_test(argv[1]);
  }
  return 0;
}


void setup() {
  
  Serial.begin(115200);

}


void loop() {

  delay(1000);  

}
