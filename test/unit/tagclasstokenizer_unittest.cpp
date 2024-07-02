#include "cuetexttokenizer_fixture"
#include <webvttxx/string>
extern "C" {
  #include "webvtt/string.c"
}

class ClassStateTokenizerTest : public CueTextTokenizerTest
{
  public:
    virtual void SetUp() {
      CueTextTokenizerTest::SetUp();
      webvtt_create_stringlist( &classes );
    }

    virtual void TearDown() {
      CueTextTokenizerTest::TearDown();
      webvtt_release_stringlist( &classes );
    }

    WebVTT::StringList parsedClasses() {
      return WebVTT::StringList( classes );
    }

    void startClassTokenize( const char *text ) {
      token_state = START_TAG_CLASS;
      pos = start = text;
      current_status = webvtt_class_state( &pos, &token_state, classes );
    }

  private:
    webvtt_stringlist *classes;
};

/*
 * Tests if the class state tokenizer parses multiple classes correctly.
 */
TEST_F(ClassStateTokenizerTest, ClassParsing)
{
  startClassTokenize( "class.subclass.subsub>" );

  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 21, currentCharPos() );
  EXPECT_EQ( START_TAG_CLASS, state() );
  EXPECT_STREQ( "class", parsedClasses()[0].utf8() );
  EXPECT_STREQ( "subclass", parsedClasses()[1].utf8() );
  EXPECT_STREQ( "subsub", parsedClasses()[2].utf8() );
}

/*
 * Tests if the class state tokenizer exits correctly upon encountering an
 * '>' character.
 */
TEST_F(ClassStateTokenizerTest, GTFinished)
{
  startClassTokenize( "class>Text" );

  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 5, currentCharPos() );
  EXPECT_EQ( START_TAG_CLASS, state() );
  EXPECT_STREQ( "class", parsedClasses()[0].utf8() );
}

/*
 * Tests if the class state state tokenizer exits correctly upon encountering an
 * '\0' character.
 */
TEST_F(ClassStateTokenizerTest, NullByteFinished)
{
  startClassTokenize( "class\0" );

  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 5, currentCharPos() );
  EXPECT_EQ( START_TAG_CLASS, state() );
  EXPECT_STREQ( "class", parsedClasses()[0].utf8() );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\n' character.
 */
TEST_F(ClassStateTokenizerTest, SpaceAnnotationStateChange)
{
  startClassTokenize( " class" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 0, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_EQ( parsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\n' character.
 */
TEST_F(ClassStateTokenizerTest, NewLineAnnotationStateChange)
{
  startClassTokenize( "\nclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 0, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_EQ( parsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\r' character.
 */
TEST_F(ClassStateTokenizerTest, CRAnnotationStateChange)
{
  startClassTokenize( "\rclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 0, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_EQ( parsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\f' character.
 */
TEST_F(ClassStateTokenizerTest, FormFeedAnnotationStateChange)
{
  startClassTokenize( "\fclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 0, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_EQ( parsedClasses().length(), 0 );
}

/*
 * Tests if the class tag state tokenizer switches to annotaion tag state and
 * returns success correctly when receiving a '\t' character.
 */
TEST_F(ClassStateTokenizerTest, TabAnnotationStateChange)
{
  startClassTokenize( "\tclass" );
  EXPECT_EQ( WEBVTT_SUCCESS, status() );
  EXPECT_EQ( 0, currentCharPos() );
  EXPECT_EQ( START_TAG_ANNOTATION, state() );
  EXPECT_EQ( parsedClasses().length(), 0 );
}
