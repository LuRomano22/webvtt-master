#include "payload_testfixture"
class PayloadLangTag : public PayloadTest {};

TEST_F(PayloadLangTag, BasicLangTag)
{
  loadVtt( "payload/lang-tag/basic-lang.vtt" );
  const Node head = getHeadOfCue( 0 );

  EXPECT_EQ( 1, head.childCount() );
  EXPECT_EQ( Node::Lang, head[ 0 ].kind() );
  EXPECT_STREQ( "en", head[ 0 ].lang().utf8() );
}

TEST_F(PayloadLangTag, InternalWithinTag)
{
  loadVtt( "payload/lang-tag/internal-within-lang.vtt" );
  const Node head = getHeadOfCue( 0 );

  EXPECT_EQ( 1, head[ 0 ][ 0 ].childCount() );
  EXPECT_EQ( Node::Bold, head[ 0 ][ 0 ].kind() );
  EXPECT_STREQ( "en", head[ 0 ][ 0 ].lang().utf8() );
}

TEST_F(PayloadLangTag, LangWithoutAnnotation)
{
  loadVtt( "payload/lang-tag/lang-without-annotation.vtt" );
  const Node head = getHeadOfCue( 0 );

  EXPECT_EQ( 1, head[ 0 ].childCount() );
  EXPECT_EQ( Node::Lang, head[ 0 ].kind() );
  EXPECT_STREQ( "", head[ 0 ].lang().utf8() );
}

TEST_F(PayloadLangTag, TwoLangTags)
{
  loadVtt( "payload/lang-tag/two-lang-tags.vtt" );
  const Node head = getHeadOfCue( 0 );

  EXPECT_EQ( 2, head.childCount() );
  EXPECT_EQ( Node::Lang, head[ 0 ].kind() );
  EXPECT_STREQ( "en", head[ 0 ].lang().utf8() );

  EXPECT_EQ( Node::Lang, head[ 1 ].kind() );
  EXPECT_STREQ( "fe", head[ 1 ].lang().utf8() );
}

TEST_F(PayloadLangTag, TwoLangInternal)
{
  loadVtt( "payload/lang-tag/two-lang-internal.vtt" );
  const Node head = getHeadOfCue( 0 );

  EXPECT_EQ( 1, head.childCount() );
  EXPECT_EQ( Node::Lang, head[ 0 ].kind() );
  EXPECT_STREQ( "en", head[ 0 ].lang().utf8() );

  EXPECT_EQ( Node::Lang, head[ 0 ][ 0 ].kind() );
  EXPECT_STREQ( "fe", head[ 0 ][ 0 ].lang().utf8() );

  EXPECT_EQ( Node::Bold, head[ 0 ][ 0 ][ 0 ].kind() );
  EXPECT_STREQ( "fe", head[ 0 ][ 0 ][ 0 ].lang().utf8() );
}
