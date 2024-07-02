#include "cuetexttokenizer_fixture"

class TagStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void tagStateTokenize( const char *text ) {
      token_state = TAG;
      pos = start = text;
      current_status = webvtt_tag_state( &pos, &token_state, &res );
    }
};

/*
 * Tests if the tag state tokenizer switches to start tag class state correctly
 * when receiving a '.' character.
 */
TEST_F(TagStateTokenizerTest, StartTagClassStateChange)
{
  tagStateTokenize( ".class" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_CLASS, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to start tag state correctly
 * when receiving a character that isn't handled by the other states character.
 */
TEST_F(TagStateTokenizerTest, StartTagStateChange)
{
  tagStateTokenize( "ruby" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG, state() );
  EXPECT_STREQ( "r", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to end state correctly when
 * receiving a '/' character.
 */
TEST_F(TagStateTokenizerTest, EndTagStateChange)
{
  tagStateTokenize( "/b" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( END_TAG, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to time stamp tag state correctly
 * when receiving a ASCII digit.
 */
TEST_F(TagStateTokenizerTest, TimeStampStateChange)
{
  tagStateTokenize( "12" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( TIME_STAMP_TAG, state() );
  EXPECT_STREQ( "1", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a ' ' character.
 */
TEST_F(TagStateTokenizerTest, SpaceAnnotationStateChange)
{
  tagStateTokenize( " Annotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\n' character.
 */
TEST_F(TagStateTokenizerTest, NewLineAnnotationStateChange)
{
  tagStateTokenize( "\nAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\r' character.
 */
TEST_F(TagStateTokenizerTest, CRAnnotationStateChange)
{
  tagStateTokenize( "\rAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\f' character.
 */
TEST_F(TagStateTokenizerTest, FormFeedAnnotationStateChange)
{
  tagStateTokenize( "\fAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer switches to annotaion tag state correctly
 * when receiving a '\t' character.
 */
TEST_F(TagStateTokenizerTest, TabAnnotationStateChange)
{
  tagStateTokenize( "\tAnnotation" );
  EXPECT_EQ( WEBVTT_UNFINISHED, status() );
  EXPECT_EQ( 1, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer exits correctly when it receives a '>'
 * character.
 */
TEST_F(TagStateTokenizerTest, GTFinished)
{
  tagStateTokenize( ">" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 0, currentCharPos() );
  EXPECT_EQ( TAG, state() );
  EXPECT_STREQ( "", parsedText() );
}

/*
 * Tests if the tag state tokenizer exits correctly when it receives a '\0'
 * character.
 */
TEST_F(TagStateTokenizerTest, NullByteFinished)
{
  tagStateTokenize( "\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 0, currentCharPos() );
  EXPECT_EQ( TAG, state() );
  EXPECT_STREQ( "", parsedText() );
}
