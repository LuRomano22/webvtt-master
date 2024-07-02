#include "cuetexttokenizer_fixture"

class TimeStampStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void timeStampTokenize( const char *text ) {
      token_state = TIME_STAMP_TAG;
      pos = start = text;
      current_status = webvtt_timestamp_state( &pos, &token_state, &res );
    }
};

/*
 * Tests if the time stamp state tokenizer parses simple text.
 */
TEST_F(TimeStampStateTokenizerTest, BasicText)
{
  timeStampTokenize( "11:00.000" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 9, currentCharPos() );
  EXPECT_EQ( TIME_STAMP_TAG, state() );
  EXPECT_STREQ( "11:00.000", parsedText() );
}

/*
 * Tests if the time stamp state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(TimeStampStateTokenizerTest, GTFinished)
{
  timeStampTokenize( "11:00.000>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 9, currentCharPos() );
  EXPECT_EQ( TIME_STAMP_TAG, state() );
  EXPECT_STREQ( "11:00.000", parsedText() );
}

/*
 * Tests if the time stamp state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(TimeStampStateTokenizerTest, NullByteFinished)
{
  timeStampTokenize( "11:00.000\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 9, currentCharPos() );
  EXPECT_EQ( TIME_STAMP_TAG, state() );
  EXPECT_STREQ( "11:00.000", parsedText() );
}
