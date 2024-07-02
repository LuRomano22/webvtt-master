#include "payload_testfixture"
class PayloadTimestampTag : public PayloadTest {};

/*
 * Verifies that time stamp cue components are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timestamp (11/27/2012)
 */
TEST_F(PayloadTimestampTag, TimestampTag)
{
  loadVtt( "payload/timestamp-tag/timestamp-tag.vtt", 1 );

  const Node timeStamp = getHeadOfCue( 0 )[ 1 ];

  ASSERT_EQ( Node::TimeStamp, timeStamp.kind() );
  expectEquals( timeStamp.timeStamp(), 0, 12, 0 );
}

/*
 * Verifies that multiple time stamp cue components are parsed.
 * From http://dev.w3.org/html5/webvtt/#webvtt-cue-timestamp (11/27/2012)
*/
TEST_F(PayloadTimestampTag, MultipleTimestampTag)
{
  loadVtt( "payload/timestamp-tag/multiple-timestamp-tag.vtt", 1 );
  const Node timeStamp0 = getHeadOfCue( 0 )[ 1 ];

  ASSERT_EQ( Node::TimeStamp, timeStamp0.kind() );
  expectEquals( timeStamp0.timeStamp(), 0, 12, 0 );

  const Node timeStamp1 = getHeadOfCue( 0 )[ 3 ];

  ASSERT_EQ( Node::TimeStamp, timeStamp1.kind() );
  expectEquals( timeStamp1.timeStamp(), 0, 13, 0 );
}
