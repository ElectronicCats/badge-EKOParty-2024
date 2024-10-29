#include "stdint.h"
#pragma once

typedef enum {
  VOLVER_SONG,
  SMB_SONG,
  ZELDA_INTRO_SONG,
  ZELDA_SONG,
  RIVAL_SONG,
  BOSS_SONG,
  SONGS_NUM
} chiptune_song_e;

typedef struct {
  chiptune_song_e idx;
  int *notes;
  int *times;
  uint16_t len;
} chiptune_t;

const int volver_notes[] = {
    370, 147, 294, 440, 147, 294, 147, 294, 147, 294, 110, 220, 110, 220, 392,
    440, 110, 220, 494, 110, 220, 440, 392, 147, 294, 440, 370, 147, 294, 370,
    147, 294, 392, 147, 294, 370, 330, 147, 294, 370, 294, 147, 294, 294, 147,
    294, 330, 147, 294, 294, 277, 147, 294, 294, 147, 294, 147, 294, 147, 294,
    494, 98,  196, 587, 98,  196, 98,  196, 98,  196, 98,  196, 98,  196, 554,
    587, 98,  196, 659, 98,  196, 587, 554, 147, 294, 587, 147, 294, 147, 294,
    440, 147, 294, 123, 247, 123, 247, 440, 494, 123, 247, 523, 123, 247, 494,
    440, 82,  165, 523, 494, 82,  165, 494, 554, 82,  165, 587, 82,  165, 554,
    494, 82,  165, 587, 554, 82,  165, 554, 82,  165, 587, 82,  165, 494, 494,
    147, 294, 554, 147, 294, 440, 440, 147, 294, 494, 147, 294, 392, 392, 147,
    294, 440, 147, 294, 147, 294, 370, 147, 294, 370, 147, 294, 440, 147, 294,
    147, 294, 147, 294, 110, 220, 110, 220, 392, 440, 110, 220, 494, 110, 220,
    440, 392, 147, 294, 440, 370, 147, 294, 370, 147, 294, 392, 147, 294, 370,
    330, 147, 294, 370, 294, 147, 294, 294, 147, 294, 330, 147, 294, 294, 277,
    147, 294};

const int volver_times[] = {
    245, 125, 125, 2417, 125, 125, 125, 125, 125, 125, 125, 125, 125,  125, 245,
    245, 125, 125, 417,  125, 125, 245, 245, 125, 125, 245, 245, 125,  125, 245,
    125, 125, 417, 125,  125, 245, 245, 125, 125, 245, 245, 125, 125,  245, 125,
    125, 417, 125, 125,  245, 245, 125, 125, 625, 125, 375, 125, 125,  125, 125,
    417, 125, 125, 2417, 125, 125, 125, 125, 125, 125, 125, 125, 125,  125, 245,
    245, 125, 125, 417,  125, 125, 245, 245, 125, 125, 875, 125, 125,  125, 125,
    875, 125, 125, 125,  125, 125, 125, 245, 245, 125, 125, 417, 125,  125, 245,
    245, 125, 125, 245,  245, 125, 125, 245, 245, 125, 125, 417, 125,  125, 245,
    245, 125, 125, 245,  245, 125, 125, 245, 125, 125, 417, 125, 125,  245, 245,
    125, 125, 417, 125,  125, 245, 245, 125, 125, 417, 125, 125, 245,  245, 125,
    125, 875, 125, 125,  125, 125, 667, 125, 125, 245, 125, 125, 2417, 125, 125,
    125, 125, 125, 125,  125, 125, 125, 125, 245, 245, 125, 125, 417,  125, 125,
    245, 245, 125, 125,  245, 245, 125, 125, 245, 125, 125, 417, 125,  125, 245,
    245, 125, 125, 245,  245, 125, 125, 245, 125, 125, 417, 125, 125,  245, 245,
    125, 417};

const int smb_notes[] = {
    659,  659,  659,  523, 659, 784,  523,  392,  330, 440, 494, 466, 440, 392,
    659,  784,  880,  698, 784, 659,  523,  587,  494, 523, 392, 330, 440, 494,
    466,  440,  392,  659, 784, 880,  698,  784,  659, 523, 587, 494, 784, 740,
    698,  622,  659,  415, 440, 523,  440,  523,  587, 784, 740, 698, 622, 659,
    1047, 1047, 1047, 784, 740, 698,  622,  659,  415, 440, 523, 440, 523, 587,
    622,  587,  523,  784, 740, 698,  622,  659,  415, 440, 523, 440, 523, 587,
    784,  740,  698,  622, 659, 1047, 1047, 1047, 784, 740, 698, 622, 659, 415,
    440,  523,  440,  523, 587, 622,  587,  523,  523, 523, 523, 523, 587, 659,
    523,  440,  392,  523, 523, 523,  523,  587,  659, 523, 523, 523, 523, 587,
    659,  523,  440,  392, 659, 659,  659,  523,  659, 784, 523, 392, 330, 440,
    494,  466,  440,  392, 659, 784,  880,  698,  784, 659, 523, 587, 494, 523,
    392,  330,  440,  494, 466, 440,  392,  659,  784, 880, 698, 784, 659, 523,
    587,  494,  659,  523, 392, 415,  440,  698,  698, 440, 494, 880, 880, 880,
    784,  698,  659,  523, 440, 392,  659,  523,  392, 415, 440, 698, 698, 440,
    494,  698,  698,  698, 659, 587,  523,  659,  523, 392, 415, 440, 698, 698,
    440,  494,  880,  880, 880, 784,  698,  659,  523, 440, 392, 523, 523, 523,
    523,  587,  659,  523, 440, 392,  523,  523,  523, 523, 587, 659, 523, 523,
    523,  523,  587,  659, 523, 440,  392,  659,  659, 659, 523, 659, 784, 659,
    523,  392,  415,  440, 698, 698,  440,  494,  880, 880, 880, 784, 698, 659,
    523,  440,  392,  659, 523, 392,  415,  440,  698, 698, 440, 494, 698, 698,
    698,  659,  587,  523, 523, 392,  330,  440,  494, 466, 440, 392, 659, 784,
    880,  698,  784,  659, 523, 587,  494,  523,  392, 330, 440, 494, 466, 440};

const int smb_times[] = {
    137, 280, 137, 137, 280, 476, 423, 137, 280, 280, 137, 137, 280, 208, 208,
    137, 280, 137, 137, 280, 137, 137, 423, 423, 137, 280, 280, 137, 137, 280,
    208, 208, 137, 280, 137, 137, 280, 137, 137, 423, 137, 137, 137, 280, 137,
    137, 137, 137, 137, 137, 137, 137, 137, 137, 280, 137, 280, 137, 476, 137,
    137, 137, 280, 137, 137, 137, 137, 137, 137, 137, 280, 423, 476, 137, 137,
    137, 280, 137, 137, 137, 137, 137, 137, 137, 137, 137, 137, 280, 137, 280,
    137, 476, 137, 137, 137, 280, 137, 137, 137, 137, 137, 137, 137, 280, 423,
    476, 137, 280, 137, 137, 280, 137, 280, 137, 476, 137, 280, 137, 137, 137,
    137, 137, 280, 137, 137, 280, 137, 280, 137, 476, 137, 280, 137, 137, 280,
    476, 423, 137, 280, 280, 137, 137, 280, 208, 208, 137, 280, 137, 137, 280,
    137, 137, 423, 423, 137, 280, 280, 137, 137, 280, 208, 208, 137, 280, 137,
    137, 280, 137, 137, 423, 137, 280, 137, 280, 137, 280, 137, 476, 208, 208,
    137, 208, 208, 137, 137, 280, 137, 476, 137, 280, 137, 280, 137, 280, 137,
    476, 137, 280, 137, 208, 208, 137, 476, 137, 280, 137, 280, 137, 280, 137,
    476, 208, 208, 137, 208, 208, 137, 137, 280, 137, 476, 137, 280, 137, 137,
    280, 137, 280, 137, 476, 137, 280, 137, 137, 137, 137, 137, 280, 137, 137,
    280, 137, 280, 137, 476, 137, 280, 137, 137, 280, 476, 137, 280, 137, 280,
    137, 280, 137, 476, 208, 208, 137, 208, 208, 137, 137, 280, 137, 476, 137,
    280, 137, 280, 137, 280, 137, 476, 137, 280, 137, 208, 208, 137, 476, 423,
    137, 280, 280, 137, 137, 280, 208, 208, 137, 280, 137, 137, 280, 137, 137,
    423, 423, 137, 280, 280, 137, 137, 280};

const int zelda_intro_notes[] = {
    1245, 1109, 932, 784, 698, 1109, 932, 784,  698,  622,  932, 784,  698, 622,
    554,  784,  698, 622, 554, 466,  698, 622,  554,  466,  392, 622,  554, 466,
    392,  349,  554, 466, 392, 349,  311, 466,  392,  349,  311, 277,  196, 233,
    349,  392,  466, 554, 698, 784,  932, 1109, 1397, 1568, 349, 466,  622, 466,
    622,  831,  523, 698, 932, 466,  622, 831,  349,  466,  622, 466,  622, 831,
    523,  698,  932, 466, 622, 831,  349, 466,  622,  466,  622, 831,  349, 466,
    622,  466,  622, 831, 523, 698,  932, 466,  622,  831,  349, 466,  622, 466,
    622,  831,  523, 698, 932, 466,  622, 831,  349,  466,  622, 466,  622, 831,
    349,  466,  622, 466, 622, 831,  523, 698,  932,  622,  831, 1109, 622, 831,
    1109, 1047, 932, 622, 831, 1047};

const int zelda_intro_times[] = {
    128, 110, 109, 110,  83,   114, 109,  108,  109,  85,   116, 110, 109, 111,
    84,  117, 112, 111,  114,  86,  135,  110,  109,  110,  83,  114, 109, 108,
    109, 85,  116, 109,  108,  109, 83,   114,  109,  108,  110, 83,  159, 139,
    142, 152, 153, 153,  155,  167, 173,  167,  173,  1877, 153, 163, 163, 160,
    160, 170, 984, 984,  1003, 163, 153,  163,  159,  169,  169, 159, 159, 169,
    153, 153, 163, 163,  153,  163, 160,  170,  170,  192,  182, 192, 153, 163,
    163, 132, 112, 132,  984,  984, 1003, 163,  153,  163,  159, 169, 169, 159,
    159, 169, 153, 153,  163,  163, 153,  163,  160,  170,  170, 192, 182, 192,
    153, 163, 163, 132,  112,  132, 1336, 1336, 1336, 666,  666, 666, 520, 520,
    520, 78,  82,  2002, 2002, 2002};

const int zelda_notes[] = {
    466, 466, 466, 466,  466,  466, 415, 466, 466, 466, 466, 466, 466, 415, 466,
    466, 466, 466, 466,  466,  349, 349, 349, 349, 349, 349, 349, 349, 349, 349,
    466, 349, 466, 466,  523,  587, 622, 698, 698, 698, 740, 831, 932, 932, 932,
    932, 831, 740, 831,  740,  698, 698, 622, 622, 698, 740, 698, 622, 554, 554,
    622, 698, 622, 554,  523,  523, 587, 659, 784, 698, 349, 349, 349, 349, 349,
    349, 349, 349, 349,  349,  466, 349, 466, 466, 523, 587, 622, 698, 698, 698,
    740, 831, 932, 1109, 1047, 880, 698, 740, 932, 880, 698, 698, 740, 932, 880,
    698, 587, 622, 740,  698,  554, 466, 523, 523, 587, 659, 784, 698, 349, 349,
    349, 349, 349, 349,  349,  349, 349, 349};

const int zelda_times[] = {
    810, 134, 67,   67,  67,  101, 134, 506,  134, 67,  67,  67,  101, 134, 607,
    134, 67,  67,   67,  101, 50,  50,  101,  50,  50,  101, 50,  50,  101, 101,
    405, 607, 101,  101, 101, 101, 101, 810,  101, 134, 134, 134, 945, 134, 134,
    134, 134, 134,  134, 134, 810, 405, 202,  101, 101, 810, 202, 202, 202, 101,
    101, 810, 202,  202, 202, 101, 101, 810,  405, 101, 50,  50,  101, 50,  50,
    101, 50,  50,   101, 101, 405, 607, 101,  101, 101, 101, 101, 810, 101, 134,
    134, 134, 1215, 405, 202, 810, 405, 1215, 405, 202, 810, 405, 810, 405, 202,
    810, 405, 810,  405, 202, 810, 405, 202,  101, 101, 810, 405, 101, 50,  50,
    101, 50,  50,   101, 50,  50,  101, 101};

const int rival_notes[] = {
    740,  784,  698,  659,  622, 587, 554,  523,  494,  466,  440, 415, 392,
    587,  392,  587,  392,  587, 392, 587,  392,  587,  392,  587, 392, 587,
    587,  392,  587,  698,  740, 392, 587,  784,  392,  587,  587, 698, 392,
    587,  587,  392,  740,  392, 587, 784,  392,  587,  784,  784, 932, 988,
    523,  784,  1047, 523,  784, 784, 932,  523,  784,  784,  523, 988, 523,
    784,  659,  1047, 523,  784, 784, 1047, 523,  784,  1047, 523, 784, 988,
    1047, 587,  880,  1175, 880, 740, 880,  587,  880,  1175, 880, 740, 880,
    587,  880,  1175, 880,  740, 880, 587,  880,  1175, 880,  740, 880, 587,
    880,  1175, 880,  740,  880, 880, 587,  1175, 880,  740,  880, 587, 880,
    587,  587,  587,  880,  698, 740, 392,  587,  784,  392,  587, 587, 698,
    392,  587,  392,  587,  740, 392, 587,  784,  392,  587,  587, 784, 587,
    392,  784,  392,  587,  932, 988, 523,  784,  1047, 523,  784, 784, 932,
    784,  523,  523,  784,  988, 523, 784,  659,  1047, 784,  523, 784, 1047,
    523,  784,  1047, 784,  523, 988, 1047, 587,  880,  1175, 880, 740, 880,
    587,  880,  1175, 880,  740, 880, 880,  587,  1175, 880,  740, 880, 587,
    880,  1175, 880,  740,  880, 587, 880,  1175, 880,  740,  880, 587, 880,
    1175, 880,  740,  880,  587, 880, 587,  587,  880,  587,  698, 740};

const int rival_times[] = {
    63,  3,   86,  89,  89,  89,  86,  86,  89,  89,  89,  91,  169, 167, 177,
    177, 180, 177, 177, 177, 174, 174, 174, 174, 180, 177, 180, 174, 177, 174,
    180, 174, 174, 174, 180, 177, 177, 172, 177, 177, 174, 177, 177, 174, 177,
    174, 177, 174, 352, 174, 177, 180, 177, 174, 177, 174, 174, 174, 174, 177,
    177, 180, 177, 177, 174, 174, 177, 174, 177, 180, 174, 174, 177, 177, 177,
    177, 177, 177, 174, 177, 177, 83,  91,  83,  91,  177, 177, 86,  91,  83,
    91,  177, 177, 86,  91,  86,  91,  172, 174, 81,  91,  86,  91,  174, 177,
    83,  91,  86,  91,  177, 174, 86,  89,  86,  89,  177, 174, 172, 177, 177,
    177, 177, 83,  174, 174, 174, 174, 177, 174, 526, 177, 177, 174, 174, 174,
    174, 177, 174, 177, 180, 177, 177, 177, 177, 177, 180, 177, 177, 177, 174,
    174, 174, 177, 177, 177, 174, 174, 174, 177, 180, 180, 174, 174, 174, 177,
    177, 177, 180, 177, 177, 177, 174, 177, 177, 174, 174, 177, 177, 83,  91,
    83,  91,  180, 177, 86,  94,  83,  91,  174, 177, 81,  94,  86,  91,  177,
    177, 83,  91,  86,  94,  174, 174, 86,  89,  83,  91,  177, 174, 83,  91,
    83,  91,  177, 177, 174, 177, 177, 177, 86,  83};

int boss_notes[] = {
    493, 493, 493, 440, 493, 587, // B4, B4, B4, A4, B4, D5
    493, 440, 349, 330,           // B4, A4, F4, E4
    493, 440, 493, 349,           // B4, A4, B4, F4
    587, 493, 440, 349, 330       // D5, B4, A4, F4, E4
};

int boss_times[] = {200, 200, 200, 300, 200, 200, 200, 300, 200,
                    400, 200, 200, 200, 300, 200, 200, 200, 300};

chiptune_t chiptune_songs[] = {
    {.idx = VOLVER_SONG,
     .notes = volver_notes,
     .times = volver_times,
     .len = 106},
    {.idx = SMB_SONG, .notes = smb_notes, .times = smb_times, .len = 308},
    {.idx = ZELDA_INTRO_SONG,
     .notes = zelda_intro_notes,
     .times = zelda_intro_times,
     .len = 132},
    {.idx = ZELDA_SONG, .notes = zelda_notes, .times = zelda_times, .len = 128},
    {.idx = RIVAL_SONG, .notes = rival_notes, .times = rival_times, .len = 17},
    {.idx = BOSS_SONG, .notes = boss_notes, .times = boss_times, .len = 18}};

void sounds_stop_music();
void sounds_play_music(chiptune_song_e song);
void play_sound(uint32_t note, uint32_t time);