#include "cuetexttokenizer_fixture"

class EscapeStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void escapeTokenize( const char *text ) {
      token_state = ESCAPE;
      pos = start = text;
      current_status = webvtt_escape_state( &pos, &token_state, &res );
    }
};

/*
 * Please note that based on the algorithm the escape state tokenizer assumes
 * that an '&' character should be at the front of the string passed in and
 * automatically appends one to it.
 */

/*
 * Tests if the escape state tokenizer exits correctly upon receiving a null
 * byte character.
 */
TEST_F(EscapeStateTokenizerTest, NullByteFinished)
{
  escapeTokenize( "Text\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( ESCAPE, state() );
  EXPECT_STREQ( "&Text", parsedText() );
}

/*
 * Tests if the escape state tokenizer exits correctly upon receiving an
 * '<' character.
 */
TEST_F(EscapeStateTokenizerTest, LTFinished)
{
  escapeTokenize( "Text<c>" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( ESCAPE, state() );
  EXPECT_STREQ( "&Text", parsedText() );
}

/*
 * Tests if the escape state tokenizer exits correctly upon encountering non
 * alpha numeric characters. It should exit upon encountering the ' ' character
 * in this example.
 */
TEST_F(EscapeStateTokenizerTest, NonAlphaNumeric)
{
  escapeTokenize( "Some Text" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 5, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "&Some ", parsedText() );
}

/*
 * Tests if the escape state tokenizer exits correctly upon encountering a
 * string that is not a valid escape sequence.
 */
TEST_F(EscapeStateTokenizerTest, IncorrectEscape)
{
  escapeTokenize( "amb; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "&amb;", parsedText() );
}

/*
 * Tests if the escape state tokenizer parses a correct ampersand escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectAmpersand)
{
  escapeTokenize( "amp; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "&", parsedText() );
}

/*
 * Tests if the escape state tokenizer parses a correct greater than escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectLT)
{
  escapeTokenize( "lt; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 3, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "<", parsedText() );
}

/*
 * Tests if the escape state tokenizer parses a correct less than escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectGT)
{
  escapeTokenize( "gt; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 3, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( ">", parsedText() );
}

/*
 * Tests if the escape state tokenizer parses a correct right-to-left escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectRLM)
{
  escapeTokenize( "rlm; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_EQ( RLM, utf16At( 0 )  );
}

/*
 * Tests if the escape state tokenizer parses a correct left-to-right escape
 * sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectLRM)
{
  escapeTokenize( "lrm; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_EQ( LRM, utf16At( 0 ) );
}

/*
 * Tests if the escape state tokenizer parses a correct non-breaking space
 * escape sequence.
 */
TEST_F(EscapeStateTokenizerTest, CorrectNBSP)
{
  escapeTokenize( "nbsp; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 5, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_EQ( NBSP, utf16At( 0 ) );
}

/*
 * Tests if the escape state tokenizer parses an extra ampersand correctly.
 */
TEST_F(EscapeStateTokenizerTest, ExtraAmpersand)
{
  escapeTokenize( "am&amp; " );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 7, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "&am&", parsedText() );
}
