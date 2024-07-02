/**
 * Copyright (c) 2013 Mozilla Foundation and Contributors
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *  - Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __INTERN_PARSER_H__
# define __INTERN_PARSER_H__
# include <webvtt/parser.h>
# include "string_internal.h"
# ifndef NDEBUG
#   define NDEBUG
# endif

# if defined(FATAL_ASSERTION)
#   undef NDEBUG
#   include <assert.h>
# else
#   if defined(BREAK_ON_ASSERTION) && !WEBVTT_OS_WIN32
static void break_on_assert();
#   endif
# endif

typedef enum
webvtt_token_t {
  BADTOKEN = -2,
  UNFINISHED = -1, /* not-token */
  BOM,
  WEBVTT, /* 'WEBVTT' */
  NEWLINE, /* /[\r\n]|(\r\n)/ */
  WHITESPACE, /* /[\t ]/ */
} webvtt_token;

typedef enum
webvtt_state_value_type_t {
  V_NONE,
  V_POINTER,
  V_INTEGER,
  V_CUE,
  V_TEXT,
  V_LNODE,
  V_INODE,
  V_TOKEN,
} webvtt_state_value_type;

typedef enum
webvtt_parse_mode_t {
  M_WEBVTT = 0,
  M_CUETEXT,
  M_SKIP_CUE,
} webvtt_parse_mode;


typedef enum
webvtt_parse_state_t {
  /**
   * WEBVTT parse states
   */
  T_INITIAL = 0,
  T_TAG,
  T_TAGCOMMENT,
  T_EOL,
  T_BODY,

  T_CUEREAD, /* Read a line of text for a cue */
  T_CUE, /* T_CUEID T_CUEPARAMS T_CUETEXT NEWLINE */
  T_CUEID, /* T_LINE !~ SEPARATOR && LINE !~ ^NOTE NEWLINE */
  T_CUEPARAMS, /* TIMESTAMP WHITESPACE? SEPARATOR WHITESPACE?
                * T_CUESETTING* NEWLINE
                */
  T_CUETEXT, /* T_LINE !~ SEPARATOR NEWLINE NEWLINE */

  T_TIMESTAMP, /* This looked like a timestamp to the lexer,
                * may or may not be valid.
                */

  /**
   * NOTE comments
   */
  T_COMMENT,

  /**
   * Cue times
   */
  T_FROM,
  T_SEP_LEFT,
  T_SEP,
  T_SEP_RIGHT,
  T_UNTIL,

  /**
   * Cue settings
   */
  T_PRECUESETTING,
  T_CUESETTING,
  T_CUESETTING_DELIMITER,
  T_CUESETTING_VALUE,
  T_SKIP_SETTING /* We have to skip a cue-setting because of an error. */

  /**
   * Cue text parse states
   */
} webvtt_parse_state;

/**
 * lexer state
 */
typedef enum
webvtt_lexer_state_t {
  L_START = 0, L_BOM0, L_BOM1, L_WEBVTT0, L_WEBVTT1, L_WEBVTT2, L_WEBVTT3,
  L_WEBVTT4, L_NEWLINE0, L_WHITESPACE
} webvtt_lexer_state;

typedef struct
webvtt_state {
  webvtt_parse_state state;
  webvtt_uint flags; /* Defaults to 0 when pushed */
  webvtt_token token;
  webvtt_state_value_type type;
  webvtt_uint back;
  webvtt_uint line;
  webvtt_uint column;
  union {
    /**
     * cue value
     */
    webvtt_cue *cue;

    /**
     * string value
     */
    webvtt_string text;

    /**
     * The cuetext parser is not currently using the state stack, and
     * because of this, 'node' is never actually used.
     *
     * It is here if the cuetext parser begins to use the/a state stack
     * in the future.
     */
    webvtt_node *node;

    /**
     * unsigned integer value
     */
    webvtt_uint value;
  } v;
} webvtt_state;

struct
webvtt_parser_t {
  webvtt_uint state;
  webvtt_uint bytes; /* number of bytes read. */
  webvtt_uint line;
  webvtt_uint column;
  webvtt_cue_fn read;
  webvtt_error_fn error;
  void *userdata;
  webvtt_bool finished;

  webvtt_uint cuetext_line; /* start line of cuetext */

  /**
   * 'mode' can have several states, it is not boolean.
   */
  webvtt_parse_mode mode;

  webvtt_state *top; /* Top parse state */
  webvtt_state astack[0x100];
  webvtt_state *stack; /* dynamically allocated stack, if 'astack' fills up */
  webvtt_uint stack_alloc; /* item capacity in 'stack' */
  webvtt_bool popped;

  /**
   * line (cue payload also stored here)
   */
  int truncate;
  webvtt_uint line_pos;
  webvtt_string line_buffer;

  /**
   * tokenizer
   */
  webvtt_lexer_state tstate;
  webvtt_uint token_pos;
  char token[0x100];
};

WEBVTT_INTERN webvtt_token
webvtt_lex( webvtt_parser self, const char *buffer, webvtt_uint *pos,
            webvtt_uint length, webvtt_bool finish );

WEBVTT_INTERN webvtt_status
webvtt_lex_word( webvtt_parser self, webvtt_string *pba, const char *buffer,
                 webvtt_uint *pos, webvtt_uint length, webvtt_bool finish );

/* Tokenize newline sequence, without incrementing 'self->line'. Returns
 * BAD_TOKEN when a newline sequence is not found. */
WEBVTT_INTERN webvtt_token
webvtt_lex_newline( webvtt_parser self, const char *buffer, webvtt_uint *pos,
                    webvtt_uint length, webvtt_bool finish );

WEBVTT_INTERN webvtt_status
webvtt_proc_cueline( webvtt_parser self, webvtt_cue *cue, webvtt_string *line );

WEBVTT_INTERN webvtt_status
webvtt_parse_align( webvtt_parser self, webvtt_cue *cue, const char *text,
                    webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status
webvtt_parse_line( webvtt_parser self, webvtt_cue *cue, const char *text,
                   webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status
webvtt_parse_position( webvtt_parser self, webvtt_cue *cue, const char *text,
                       webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status
webvtt_parse_size( webvtt_parser self, webvtt_cue *cue, const char *text,
                   webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN webvtt_status
webvtt_parse_vertical( webvtt_parser self, webvtt_cue *cue, const char *text,
                       webvtt_uint *pos, webvtt_uint len );

WEBVTT_INTERN int
webvtt_parse_timestamp( const char *b, int *tokenLength,
                        webvtt_timestamp *result );

WEBVTT_INTERN webvtt_status
do_push( webvtt_parser self, webvtt_uint token, webvtt_uint back,
         webvtt_uint state, void *data, webvtt_state_value_type type,
         webvtt_uint line, webvtt_uint column );

WEBVTT_INTERN webvtt_status
webvtt_read_cuetext( webvtt_parser self, const char *b, webvtt_uint *ppos,
                    webvtt_uint len, webvtt_bool finish );

WEBVTT_INTERN webvtt_status
webvtt_proc_cuetext( webvtt_parser self, const char *b, webvtt_uint *ppos,
                    webvtt_uint len, webvtt_bool finish );

WEBVTT_INTERN webvtt_status
webvtt_parse_timings_and_settings( webvtt_parser self, const webvtt_string *line );

WEBVTT_INTERN int
parse_cueparams( webvtt_parser self, const char *text, webvtt_uint len,
                 webvtt_cue *cue );

/**
 * Flags which can apply additional meaning to a token. find_token() will
 * test for only the actual token and ignore the additional flags.
 */
typedef
enum webvtt_token_flags_t
{
  /* Number can be positive */
  TF_POSITIVE = 0x80000000,

  /* Number can be negative */
  TF_NEGATIVE = 0x40000000,
  /* (token & TF_SIGN_MASK) == combination of TF_POSITIVE and
     TF_NEGATIVE, which indicate what values a number token is allowed
     to be */
  TF_SIGN_MASK = ( TF_POSITIVE | TF_NEGATIVE ),

  /* (token & TF_FLAGS_MASK) == webvtt_token_flags value
     that is being asked for */
  TF_FLAGS_MASK = TF_SIGN_MASK,

  /* (token & TF_TOKEN_MASK) == webvtt_token value */
  TF_TOKEN_MASK = ( 0xFFFFFFFF & ~TF_FLAGS_MASK ),
} webvtt_token_flags;

/**
 * Return non-zero if a token is found in a NULL-terminated array of tokens, or
 * zero if not.
 *
 * Unlike find_token(), token_in_list() does not make use of
 * webvtt_token_flags and thus requiers an exact match.
 */
WEBVTT_INTERN webvtt_bool
token_in_list( webvtt_token search_for, const webvtt_token token_list[] );

/**
 * Return the index of a token in a NULL-terminated array of tokens,
 * or -1 if the token is not found.
 *
 * find_token() will search for an occurrence of `token' in a list
 * where webvtt_token_flags are used. For instance, if the list of
 * tokens contains { TF_POSITIVE | INTEGER, TF_POSITIVE | PERCENTAGE,
 * 0 }, find_token() will return a match for INTEGER or PERCENTAGE if
 * either is searched for.
 */
WEBVTT_INTERN int
find_token( webvtt_token search_for, const webvtt_token token_list[] );

WEBVTT_INTERN webvtt_int64
webvtt_parse_int( const char **pb, int *pdigits );

#define BAD_TIMESTAMP(ts) ( ( ts ) == 0xFFFFFFFFFFFFFFFF )

#ifdef FATAL_ASSERTION
#  define SAFE_ASSERT(condition) assert(condition)
#  define DIE_IF(condition) assert( !(condition) )
#else
#  ifdef BREAK_ON_ASSERTION
static void
break_on_assert(void) {
#if WEBVTT_OS_WIN32
  /* __declspec(dllimport) should work for cross compiling gcc as well */
  __declspec(dllimport) void __stdcall DebugBreak( void );
  DebugBreak();
#else
  volatile int *ptr = (volatile int *)0;
  *ptr = 1;
#endif
}
#    define SAFE_ASSERT(condition) \
if( !(condition) ) { \
  break_on_assert(); \
  return WEBVTT_FAILED_ASSERTION; \
}
#    define DIE_IF(condition) \
if( (condition) ) { \
  break_on_assert(); \
}
#  else
#    define SAFE_ASSERT(condition) \
if( !(condition) ) { \
  return WEBVTT_FAILED_ASSERTION; \
}
#    define DIE_IF(condition)
#  endif
#endif

#define __ERROR_AT_OR(errno, line, column, __or) \
do \
{ \
  if( !self->error \
    || self->error( (self->userdata), (line), (column), (errno) ) < 0 ) { \
    __or \
  } \
} while(0)

#define ERROR_AT_OR(errno, line, column, ret) \
  __ERROR_AT_OR(errno,line,column,return (ret);)

#define WARNING_AT(errno, line, column) \
  __ERROR_AT_OR(errno,line,column,)

#define ERROR_AT(errno, line, column) \
  ERROR_AT_OR( (errno), (line), (column), WEBVTT_PARSE_ERROR )

#define ERROR(error) \
  ERROR_AT( (error), (self->line), (self->column) )

#define ERROR_AT_COLUMN(error, column) \
  ERROR_AT( (error), (self->line), (column) )
#endif
