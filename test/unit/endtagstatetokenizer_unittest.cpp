#include "cuetexttokenizer_fixture"

class EndTagStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void endTagTokenize( const char *text ) {
      token_state = END_TAG;
      pos = start = text;
      current_status = webvtt_end_tag_state( &pos, &token_state, &res );
    }
};

/*
 * Tests if the end tag state tokenizer parses simple text.
 */
TEST_F(EndTagStateTokenizerTest, BasicText)
{
  endTagTokenize( "ruby" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( END_TAG, state() );
  EXPECT_STREQ( "ruby", parsedText() );
}

/*
 * Tests if the end tag state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(EndTagStateTokenizerTest, GTFinished)
{
  endTagTokenize( "ruby>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( END_TAG, state() );
  EXPECT_STREQ( "ruby", parsedText() );
}

/*
 * Tests if the end tag state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(EndTagStateTokenizerTest, NullByteFinished)
{
  endTagTokenize( "ruby\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( END_TAG, state() );
  EXPECT_STREQ( "ruby", parsedText() );
}
