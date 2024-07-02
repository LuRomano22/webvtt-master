#include "cuetexttokenizer_fixture"

class AnnotationStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    void annotationTagTokenize( const char *text ) {
      token_state = START_TAG_ANNOTATION;
      pos = start = text;
      current_status = webvtt_annotation_state( &pos, &token_state, &res );
    }
};

/*
 * Tests if the annotation state tokenizer parses simple text.
 */
TEST_F(AnnotationStateTokenizerTest, BasicText)
{
  annotationTagTokenize( "Annotation" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 10, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "Annotation", parsedText() );
}

/*
 * Tests if the annotation state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(AnnotationStateTokenizerTest, GTFinished)
{
  annotationTagTokenize( "Annotation>Text" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 10, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "Annotation", parsedText() );
}

/*
 * Tests if the annotation state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(AnnotationStateTokenizerTest, NullByteFinished)
{
  annotationTagTokenize( "Annotation\0" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 10, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_STREQ( "Annotation", parsedText() );
}
