#include "cuetexttokenizer_fixture"

class DataStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void dataTokenize( const char *text ) {
      token_state = DATA;
      pos = start = text;
      current_status = webvtt_data_state( &pos, &token_state, &res );
    }
};

/*
 * Tests if the data state tokenizer will parse basic text.
 */
TEST_F(DataStateTokenizerTest, BasicText)
{
  dataTokenize( "Some Text Here" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 14, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "Some Text Here", parsedText() );
}

/*
 * Tests if the data state tokenizer will switch to the escape state if it
 * encounters an '&' character.
 */
TEST_F(DataStateTokenizerTest, EscapeStateChange)
{
  dataTokenize( "&amp" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( ESCAPE, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the data state tokenizer returns WEBVTT_SUCCESS if it reaches a '<'
 * character after it has parsed some text.
 */
TEST_F(DataStateTokenizerTest, LTFinishedToken)
{
  dataTokenize( "Text <b>" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 5, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "Text ", parsedText() );
}

/*
 * Tests if the data state tokenizer switches to the tag state if it encounters
 * an '<' character and it hasn't parsed any text yet.
 */
TEST_F(DataStateTokenizerTest, LTStartedToken)
{
  dataTokenize( "<b>" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( TAG, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the data state tokenizer returns WEBVTT_SUCCESS upon reaching the
 * '\0' character.
 */
TEST_F(DataStateTokenizerTest, NullByteFinishedToken)
{
  dataTokenize( "Text \0" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 5, currentCharPos() );
  EXPECT_EQ( DATA, state() );
  EXPECT_STREQ( "Text ", parsedText() );
}
