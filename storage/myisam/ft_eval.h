/* Copyright (c) 2000-2002, 2005 MySQL AB


   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA */


/* Written by Sergei A. Golubchik, who has a shared copyright to this code */

const char **stopwordlist=ft_precompiled_stopwords;

#define MAX_REC_LENGTH 128
#define MAX_BLOB_LENGTH 60000
char record[MAX_REC_LENGTH], read_record[MAX_REC_LENGTH+MAX_BLOB_LENGTH];
char blob_record[MAX_BLOB_LENGTH+20*20];

char *filename= (char*) "EVAL";

int silent=0, error=0;

uint key_length=MAX_BLOB_LENGTH,docid_length=32;
char *d_file, *q_file;
FILE *df,*qf;

MI_COLUMNDEF recinfo[3];
MI_KEYDEF keyinfo[2];
HA_KEYSEG keyseg[10];

#define SWL_INIT 500
#define SWL_PLUS 50

#define MAX_LINE_LENGTH 128
char line[MAX_LINE_LENGTH];