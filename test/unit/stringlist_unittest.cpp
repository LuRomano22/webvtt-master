#include <gtest/gtest.h>
#include <webvttxx/string>

class StringListTest : public ::testing::Test
{
public:
  virtual void SetUp() {
    webvtt_create_stringlist( &list );
  }

  virtual void TearDown() {
    webvtt_release_stringlist( &list );
  }

  void pop( webvtt_string *out ) {
    EXPECT_EQ( 1, webvtt_stringlist_pop( list, out ) );
  }

  void pop() {
    webvtt_string str;
    pop( &str );
    webvtt_release_string( &str );
  }

  void push( const char *text ) {
    webvtt_string str;
    EXPECT_EQ( WEBVTT_SUCCESS, 
               webvtt_create_string_with_text( &str, text, -1 ) );
    EXPECT_EQ( WEBVTT_SUCCESS, webvtt_stringlist_push( list, &str ) );
    webvtt_release_string( &str );
  }

  webvtt_uint16 alloc() {
    return list->alloc;
  }

  webvtt_uint16 length() {
    return list->length;
  }

  const char * stringAt( webvtt_uint16 index ) {
    if( index > list->length - 1 ) {
      return 0;
    }
    return webvtt_string_text( list->items + index );
  }

private:
  webvtt_stringlist *list;
};

TEST_F(StringListTest, StringListPush)
{
  push( "This is a test." );

  EXPECT_EQ( 8, alloc() );
  EXPECT_EQ( 1, length() );\
  EXPECT_STREQ( "This is a test.", stringAt( 0 ) );
}

TEST_F(StringListTest, StringListPushGrow)
{
  push( "This is a test." );
  push( "We're adding strings." );
  push( "In order to grow the list." );
  push( "Four is the first amount.");

  EXPECT_EQ( 16, alloc() );
  EXPECT_EQ( 4, length() );
}

TEST_F(StringListTest, StringListPop)
{
  webvtt_string str;

  push( "This is a test." );
  pop( &str );

  EXPECT_EQ( 8, alloc() );
  EXPECT_EQ( 0, length() );
  EXPECT_STREQ( "This is a test.", webvtt_string_text( &str ) );
  webvtt_release_string( &str );
}

TEST_F(StringListTest, PushAndPop)
{
  push( "This is a test." );
  pop();
  push("Random new test.");

  EXPECT_EQ( 8, alloc() );
  EXPECT_EQ( 1, length() );
  EXPECT_STREQ( "Random new test.", stringAt( 0 ) );
}
