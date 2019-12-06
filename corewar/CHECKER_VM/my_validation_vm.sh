#!/usr/bin/env bash

CYAN='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
YEL='\033[1;32m'
NC='\033[0m'

# путь до родного файла
PATH_TO_VM=..
OUR_VM=corewar
ORIG_VM=corewar_original
FIRST_ARRAY_CH=./champ/*.cor
SEC_ARRAY_CH=./champ/*.cor
TH_ARRAY_CH=./champ/*.cor
i=0

rm error*

# Цикл 1 - проход по каждому игроку

echo "\n${YEL}ONE_CHAMP ${NC} \n"

for f in $FIRST_ARRAY_CH
do
  $PATH_TO_VM/$OUR_VM -debug $f > our_output
  ./$ORIG_VM -v 6 -a $f > origin_output
  if diff ./our_output ./origin_output &> /dev/null; then
    echo "${f} - ${GREEN}[OK]${NC}"
  else
    echo "${f} - ${RED}[KO]${NC}"
    echo "${f}
    __________
    " > error_$i
    diff ./our_output ./origin_output >> error_$i
    echo "__________
    " >> error_$i
    fi
    i=$((i+1))
done


# Цикл 2 - проход по каждому игроку с каждым игроком из массива 2 (1 - 2 массивы)

echo "\n${YEL}TWO CHAMPIONS ${NC} \n"
array_two=()
for f in $FIRST_ARRAY_CH
do
  for fo in $SEC_ARRAY_CH
  do
    $PATH_TO_VM/$OUR_VM -debug $f $fo > our_output
    ./$ORIG_VM -v 6 -a $f $fo > origin_output
    if diff ./our_output ./origin_output &> /dev/null; then
    echo "${f} ${fo} - ${GREEN}[OK]${NC}"
  else
    echo "${f} ${fo} - ${RED}[KO]${NC}"
    echo "${f} ${fo}\n________________________________\n" > error_$i
    diff ./our_output ./origin_output >> error_$i
    echo "________________________________\n" >> error_$i
    fi
    i=$((i+1))
  done
done

# Цикл 3 - проход по каждому 1-му со 2-м с каждым 3 (1 - 2 -3 массивы) god help

echo "\n${YEL}THREE CHAMPIONS ${NC} \n"

for f in $FIRST_ARRAY_CH
do
  for fo in $SEC_ARRAY_CH
  do
    for foo in $TH_ARRAY_CH
    do
      $PATH_TO_VM/$OUR_VM -debug $f $fo $foo > our_output
      ./$ORIG_VM -v 6 -a $f $fo $foo > origin_output
      if diff ./our_output ./origin_output &> /dev/null; then
       echo "${f} ${fo} ${foo}- ${GREEN}[OK]${NC}"
      else
       echo "${f} ${fo} ${foo} - ${RED}[KO]${NC}"
        echo "${f} ${fo} ${foo}\n________________________________\n" > error_$i
       diff ./our_output ./origin_output >> error_$i
      echo "________________________________\n" >> error_$i
     fi
     i=$((i+1))
    done
  done
done

rm origin_output our_output
