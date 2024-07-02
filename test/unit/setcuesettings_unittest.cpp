#include <gtest/gtest.h>
extern "C" {
#include "webvtt/cue_internal.h"
}

class SetCueSetting : public ::testing::Test
{
public:
  virtual void SetUp() {
    ASSERT_EQ( WEBVTT_SUCCESS, ::webvtt_create_cue( &cue ) );
  }
  virtual void TearDown() {
    ::webvtt_release_cue( &cue );
  }

  ::webvtt_status setMulti( const char *str ) {
    ::webvtt_status s;
    ::webvtt_string settings;
    s = ::webvtt_create_string_with_text( &settings, str, -1 );
    if( s == WEBVTT_SUCCESS ) {
      s = ::webvtt_cue_set_settings( cue, &settings );
      ::webvtt_release_string( &settings );
    }
    return s;
  }

  ::webvtt_status set( const char *str ) {
    return ::webvtt_cue_set_setting_from_string( cue, str );
  }

  ::webvtt_status setAlign( const char *value ) {
    return ::webvtt_cue_set_align( cue, value );
  }

  ::webvtt_status setLine( const char *value ) {
    return ::webvtt_cue_set_line( cue, value );
  }

  ::webvtt_status setPosition( const char *value ) {
    return ::webvtt_cue_set_position( cue, value );
  }

  ::webvtt_status setSize( const char *value ) {
    return ::webvtt_cue_set_size( cue, value );
  }

  ::webvtt_status setVertical( const char *value ) {
    return ::webvtt_cue_set_vertical( cue, value );
  }

  bool snapToLines() const { return !!cue->snap_to_lines; }
  webvtt_align_type align() const { return cue->settings.align; }
  int line() const { return cue->settings.line; }
  int position() const { return cue->settings.position; }
  int size() const { return cue->settings.size; }
  webvtt_vertical_type vertical() const { return cue->settings.vertical; }

private:
  ::webvtt_cue *cue;
};

class SetAlign : public SetCueSetting {};
class SetLine : public SetCueSetting {};
class SetPosition : public SetCueSetting {};
class SetSize : public SetCueSetting {};
class SetVertical : public SetCueSetting {};

TEST_F(SetAlign, Start)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setAlign("start"));
  EXPECT_EQ(WEBVTT_ALIGN_START, align());
}

TEST_F(SetAlign, Middle)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setAlign("middle"));
  EXPECT_EQ(WEBVTT_ALIGN_MIDDLE, align());
}

TEST_F(SetAlign, End)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setAlign("end"));
  EXPECT_EQ(WEBVTT_ALIGN_END, align());
}

TEST_F(SetAlign, Left)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setAlign("left"));
  EXPECT_EQ(WEBVTT_ALIGN_LEFT, align());
}

TEST_F(SetAlign, Right)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setAlign("right"));
  EXPECT_EQ(WEBVTT_ALIGN_RIGHT, align());
}

TEST_F(SetAlign, Bad)
{
  EXPECT_EQ(WEBVTT_BAD_ALIGN, setAlign("bad-align"));
}

TEST_F(SetLine, Negative)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setLine("-1"));
  EXPECT_EQ(-1, line());
  EXPECT_TRUE(snapToLines());
}

TEST_F(SetLine, NegativePercent)
{
  EXPECT_EQ(WEBVTT_BAD_LINE, setLine("-1%"));
}

TEST_F(SetLine, Percent)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setLine("5%"));
  EXPECT_EQ(5, line());
  EXPECT_FALSE(snapToLines());
}

TEST_F(SetLine, BadChar)
{
  EXPECT_EQ(WEBVTT_BAD_LINE, setLine("5z"));
}

TEST_F(SetLine, DashNotAtStart)
{
  EXPECT_EQ(WEBVTT_BAD_LINE, setLine("5-"));
}

TEST_F(SetLine, PercentNotAtEnd)
{
  EXPECT_EQ(WEBVTT_BAD_LINE, setLine("5%4"));
}

TEST_F(SetPosition, 0)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setPosition("0%"));
  EXPECT_EQ(0, position());
}

TEST_F(SetPosition, 100)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setPosition("100%"));
  EXPECT_EQ(100, position());
}

TEST_F(SetPosition, OutOfRange)
{
  EXPECT_EQ(WEBVTT_BAD_POSITION, setPosition("-1%"));
  EXPECT_NE(-1, position());
  EXPECT_EQ(WEBVTT_BAD_POSITION, setPosition("101%"));
  EXPECT_NE(101, position());
}

TEST_F(SetPosition, PercentNotAtEnd)
{
  EXPECT_EQ(WEBVTT_BAD_POSITION, setPosition("5%4"));
}

TEST_F(SetPosition, BadChar)
{
  EXPECT_EQ(WEBVTT_BAD_POSITION, setPosition("1-"));
  EXPECT_EQ(WEBVTT_BAD_POSITION, setPosition("1z"));
}

TEST_F(SetPosition, NotPercent)
{
  EXPECT_EQ(WEBVTT_BAD_POSITION, setPosition("1"));
}

TEST_F(SetSize, 0)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setSize("0%"));
  EXPECT_EQ(0, size());
}

TEST_F(SetSize, 100)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setSize("100%"));
  EXPECT_EQ(100, size());
}

TEST_F(SetSize, OutOfRange)
{
  EXPECT_EQ(WEBVTT_BAD_SIZE, setSize("-1%"));
  EXPECT_NE(-1, size());
  EXPECT_EQ(WEBVTT_BAD_SIZE, setSize("101%"));
  EXPECT_NE(101, size());
}

TEST_F(SetSize, PercentNotAtEnd)
{
  EXPECT_EQ(WEBVTT_BAD_SIZE, setSize("5%4"));
}

TEST_F(SetSize, BadChar)
{
  EXPECT_EQ(WEBVTT_BAD_SIZE, setSize("1-"));
  EXPECT_EQ(WEBVTT_BAD_SIZE, setSize("1z"));
}

TEST_F(SetSize, NotPercent)
{
  EXPECT_EQ(WEBVTT_BAD_SIZE, setSize("1"));
}

TEST_F(SetVertical, RL)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setVertical("rl"));
  EXPECT_EQ(WEBVTT_VERTICAL_RL, vertical());
}

TEST_F(SetVertical, LR)
{
  EXPECT_EQ(WEBVTT_SUCCESS, setVertical("lr"));
  EXPECT_EQ(WEBVTT_VERTICAL_LR, vertical());
}

TEST_F(SetVertical, Bad)
{
  EXPECT_EQ(WEBVTT_BAD_VERTICAL, setVertical("bad-vertical"));
  EXPECT_EQ(WEBVTT_HORIZONTAL, vertical());
}

TEST_F(SetCueSetting, ColonFirst)
{
  EXPECT_EQ(WEBVTT_BAD_CUESETTING, set(":rl"));
}

TEST_F(SetCueSetting, ColonLast)
{
  EXPECT_EQ(WEBVTT_BAD_CUESETTING, set("vertical:"));
}

TEST_F(SetCueSetting, NoWhitespace)
{
  EXPECT_EQ(WEBVTT_BAD_ALIGN, set("align:leftposition:10%"));
  EXPECT_EQ(WEBVTT_BAD_LINE, set("line:-1position:10%"));
  EXPECT_EQ(WEBVTT_BAD_POSITION, set("position:10%size:10%"));
  EXPECT_EQ(WEBVTT_BAD_SIZE, set("size:10%position:10%"));
  EXPECT_EQ(WEBVTT_BAD_VERTICAL, set("vertical:rlposition:10%"));
}


