#pragma once

#include <stdio.h>
#include <stdint.h>
#include "../tipos.h"

#ifndef __ORDENACAO_H__
#define __ORDENACAO_H__

erro_t insertionSort();
erro_t bubbleSort();
erro_t radixSort();
erro_t heapSort();
erro_t mergeSort();
erro_t quickSort();

#endif