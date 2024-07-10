/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int pid, status;
  if (command == NULL) {
    return 1;
  }
  pid = fork();
  if (pid < 0) {
    return -1;
  }
  if (pid != 0) {
    while(wait(&status) != pid)
    ;
  } else {
    execl("/bin/sh", "sh", "-c", command, NULL);
    exit(127);
  }
  return status;
}



/* 実行例

//コンパイル時、エラーがないか
% make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c

//コマンドラインで実行した結果
% ls -l
total 616
-rw-r--r--  1 mitsuya  staff     143  7  4 10:00 Makefile
-rw-r--r--  1 mitsuya  staff    2795  7  4 10:00 README.md
-rw-r--r--  1 mitsuya  staff  238232  7  4 10:00 README.pdf
-rwxr-xr-x  1 mitsuya  staff   50358  7 10 09:14 mysysmain
-rw-r--r--  1 mitsuya  staff     925  7  4 10:00 mysysmain.c
-rw-r--r--  1 mitsuya  staff    2257  7 10 09:13 mysystem.c
-rw-r--r--  1 mitsuya  staff      90  7  4 10:00 mysystem.h


//mysystemとsystemの結果を表示
% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 mitsuya  staff     143  7  4 10:00 Makefile
-rw-r--r--  1 mitsuya  staff    2795  7  4 10:00 README.md
-rw-r--r--  1 mitsuya  staff  238232  7  4 10:00 README.pdf
-rwxr-xr-x  1 mitsuya  staff   50358  7 10 09:14 mysysmain
-rw-r--r--  1 mitsuya  staff     925  7  4 10:00 mysysmain.c
-rw-r--r--  1 mitsuya  staff    2257  7 10 09:13 mysystem.c
-rw-r--r--  1 mitsuya  staff      90  7  4 10:00 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 mitsuya  staff     143  7  4 10:00 Makefile
-rw-r--r--  1 mitsuya  staff    2795  7  4 10:00 README.md
-rw-r--r--  1 mitsuya  staff  238232  7  4 10:00 README.pdf
-rwxr-xr-x  1 mitsuya  staff   50358  7 10 09:14 mysysmain
-rw-r--r--  1 mitsuya  staff     925  7  4 10:00 mysysmain.c
-rw-r--r--  1 mitsuya  staff    2257  7 10 09:13 mysystem.c
-rw-r--r--  1 mitsuya  staff      90  7  4 10:00 mysystem.h
retval = 00000000

//引数がない時、使い方を表示
% ./mysysmain
使い方 : ./mysysmain コマンド文字列


*/
