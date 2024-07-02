#include "cuetexttokenizer_fixture"

class StartTagStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void startTagTokenize( const char *text ) {
      token_state = START_TAG;
      pos = start = text;
      current_status = webvtt_start_tag_state( &pos, &token_state, &res );
    }
};

/*
 * Tests if the start tag state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(StartTagStateTokenizerTest, GTFinished)
{
  startTagTokenize( "ruby>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 4, currentCharPos() );
  EXPECT_EQ( START_TAG, state() );
  EXPECT_STREQ( "ruby", parsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to start tag class state
 * upon encountering an '.' character.
 */
TEST_F(StartTagStateTokenizerTest, StartTagClassStateChange)
{
  startTagTokenize( "ruby.class" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 5, currentCharPos() );
  EXPECT_EQ( START_TAG_CLASS, state() );
  EXPECT_STREQ( "ruby", parsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\n' character.
 */
TEST_F(StartTagStateTokenizerTest, SpaceAnnotationStateChange)
{
  startTagTokenize( " Annotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\n' character.
 */
TEST_F(StartTagStateTokenizerTest, NewLineAnnotationStateChange)
{
  startTagTokenize( "\nAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\r' character.
 */
TEST_F(StartTagStateTokenizerTest, CRAnnotationStateChange)
{
  startTagTokenize( "\rAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\f' character.
 */
TEST_F(StartTagStateTokenizerTest, FormFeedAnnotationStateChange)
{
  startTagTokenize( "\fAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the start tag state tokenizer switches to annotaion tag state
 * correctly when receiving a '\t' character.
 */
TEST_F(StartTagStateTokenizerTest, TabAnnotationStateChange)
{
  startTagTokenize( "\tAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}
