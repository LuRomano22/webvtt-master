#include "cue_testfixture"
class CueSetting : public CueTest { };
/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of
 * different types, delimited by U+0009 (tab)
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 5.1. Collect a sequence of characters that are not space characters.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, MultipleCueSettings2Tab)
{
  loadVtt( "cue-settings/2-cue-settings-0x09.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
  EXPECT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of
 * different types, delimited by U+0020 (space)
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 5.1. Collect a sequence of characters that are not space characters.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, MultipleCueSettings2Space)
{
  loadVtt( "cue-settings/2-cue-settings-0x20.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
  EXPECT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser correctly parses a combination of 2 cue settings of
 * different types, delimited by a combination of U+0020 (space) and U+0009
 * (tab)
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 5.1. Collect a sequence of characters that are not space characters.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, MultipleCueSettings2Mixed)
{
  loadVtt( "cue-settings/2-cue-settings-mixed.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
  EXPECT_EQ( 50, getCue( 0 ).relativeLinePositionPercentage() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace
 * (11/27/2012):
 *
 * The step skip whitespace means that the user agent must collect a sequence of
 * characters that are space characters. ...the collected characters are not
 * used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x20)
{
  loadVtt( "cue-settings/delimiter-0x20.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace
 * (11/27/2012):
 *
 * The step skip whitespace means that the user agent must collect a sequence of
 * characters that are space characters. ...the collected characters are not
 * used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x20Sequence)
{
  loadVtt( "cue-settings/delimiter-0x20-sequence.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace
 * (11/27/2012):
 *
 * The step skip whitespace means that the user agent must collect a sequence of
 * characters that are space characters. ...the collected characters are not
 * used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x09)
{
  loadVtt( "cue-settings/delimiter-0x09.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace
 * (11/27/2012):
 *
 * The step skip whitespace means that the user agent must collect a sequence of
 * characters that are space characters. ...the collected characters are not
 * used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, Delimiter0x09Sequence)
{
  loadVtt( "cue-settings/delimiter-0x09-sequence.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verifies that the parser can deal with the U+0020 delimiter
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 *
 * From
 * http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-separated-tokens
 * (11/27/2012):
 *
 * 4. Skip whitespace
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#skip-whitespace
 * (11/27/2012):
 *
 * The step skip whitespace means that the user agent must collect a sequence of
 * characters that are space characters. ...the collected characters are not
 * used.
 *
 * From http://dev.w3.org/html5/spec//common-microsyntaxes.html#space-character
 * (11/27/2012):
 *
 * The space characters, for the purposes of this specification, are U+0020
 * SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 */
TEST_F(CueSetting, DelimiterMixed)
{
  loadVtt( "cue-settings/delimiter-mixed.vtt", 1 );
  EXPECT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  EXPECT_TRUE( getCue( 0 ).isVerticalLeftToRight() );
}

/**
 * Verify the parser accepts duplicate settings.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 * 2. For each token setting in the list settings...
 */
TEST_F(CueSetting, SameCueSetting)
{
  loadVtt( "cue-settings/2-same-settings.vtt", 1 );
  ASSERT_LE( 1, errorCount() ) << "This file should contain at least 1 error";
  EXPECT_EQ( 1, errorCount() ) << "This file should contain 1 error";
  /**
   * Parser will successfully parse duplicate settings so there will be no
   * error.  The settings are parsed in order so that the right most (last in
   * the list) one is used.
   */
  ASSERT_TRUE( getCue( 0 ).isVerticalRightToLeft() );
  /**
   * We're expecting a WEBVTT_VERTICAL_ALREADY_SET error on the 37th column of
   * the 3rd line We can probably make this smarter, like
   * WEBVTT_EXPECTED_CUESETTING_DELIMITER or something
   */
  expectEquals( getError( 0 ), WEBVTT_VERTICAL_ALREADY_SET, 3, 37 );
}

/**
 * Test that the parser takes everything to the right of the first colon in a
 * setting.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *
 * 1. Let settings be the result of splitting input on spaces.
 * 2. For each token setting in the list settings...
 * 3. Let value be the trailing substring of setting starting from the
 *    character immediately after the first U+003A COLON character (:) in that
 *    string.
 */
TEST_F(CueSetting, BadDelimiter)
{
  loadVtt( "cue-settings/bad-delimiter.vtt", 1 );
  ASSERT_LE( 1, errorCount() ) << "This file should contain at least 1 error";
  EXPECT_EQ( 1, errorCount() ) << "This file should contain 1 error";

  /**
   * The parser should try to use "vertical" as keyword and "lr;line:50%" as
   * value.  Writing direction should "horizontal" because the malformed setting
   * should be skipped and "horizontal" is default.
   */
  expectDefaultVerticalSetting( getCue( 0 ) );

  /**
   * We're expecting a WEBVTT_VERTICAL_BAD_VALUE error on the 34th column of
   * the 3rd line (Beginning of value token)
   */
  expectEquals( getError( 0 ), WEBVTT_VERTICAL_BAD_VALUE, 3, 25 );
}

/**
 * Test that the parser does not require a spacing character between cue end
 * time timestamp and settings. There cannot be four digits in a row after the
 * cue end time timestamp decimal.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-webvtt-cue-timings-and-settings
 * (11/21/2012):
 *
 * 10. Collect a WebVTT timestamp.
 * 11. Let remainder be the trailing substring of input starting at position.
 * 12. Parse the WebVTT settings given by remainder for cue.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-a-webvtt-timestamp (11/21/2012):
 * 14. Collect a sequence of characters that are ASCII digits, and let string be
 *     the collected substring.
 * 15. If string is not exactly three characters in length, return an error and
 *     abort these steps.
 */
TEST_F(CueSetting, BadDelimiter2)
{
  loadVtt( "cue-settings/bad-delimiter2.vtt", 1 );
  ASSERT_LE( 2, errorCount() ) << "This file should contain at least 2 error";
  EXPECT_EQ( 2, errorCount() ) << "This file should contain 2 error";

  /**
   * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 24th column of
   * the 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_EXPECTED_WHITESPACE, 3, 24 );
  /**
   * Expecting WEBVTT_INVALID_CUESETTING on the 24th column of the 3rd line
   * (^line is not a valid keyword)
   */
  expectEquals( getError( 1 ), WEBVTT_INVALID_CUESETTING, 3, 24 );
}

/**
 * Test that the parser does not require a spacing character between cue end
 * time timestamp and settings. There cannot be four digits in a row after the
 * cue end time timestamp decimal.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-webvtt-cue-timings-and-settings
 * (11/21/2012):
 *
 * 10. Collect a WebVTT timestamp.
 * 11. Let remainder be the trailing substring of input starting at position.
 * 12. Parse the WebVTT settings given by remainder for cue.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-a-webvtt-timestamp (11/21/2012):
 * 14. Collect a sequence of characters that are ASCII digits, and let string be
 *     the collected substring.
 * 15. If string is not exactly three characters in length, return an error and
 *     abort these steps.
 */
TEST_F(CueSetting, NoDelimiter)
{
  loadVtt( "cue-settings/no-delimiter.vtt", 1 );
  ASSERT_LE( 1, errorCount() ) << "This file should contain at least 1 error";
  EXPECT_EQ( 1, errorCount() ) << "This file should contain 1 error";

  /**
   * We're expecting a WEBVTT_EXPECTED_WHITESPACE error on the 24th column of
   * the 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_EXPECTED_WHITESPACE, 3, 24 );
}

/**
 * Test that the parser does not require a spacing character between cue end
 * time timestamp and settings. There cannot be four digits in a row after the
 * cue end time timestamp decimal.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-webvtt-cue-timings-and-settings
 * (11/21/2012):
 *
 * 10. Collect a WebVTT timestamp.
 * 11. Let remainder be the trailing substring of input starting at position.
 * 12. Parse the WebVTT settings given by remainder for cue.
 *
 * From http://dev.w3.org/html5/webvtt/#collect-a-webvtt-timestamp (11/21/2012):
 * 14. Collect a sequence of characters that are ASCII digits, and let string be
 *     the collected substring.
 * 15. If string is not exactly three characters in length, return an error and
 *     abort these steps.
 */
TEST_F(CueSetting, DigitDelimiter)
{
  loadVtt( "cue-settings/digit-delimiter.vtt", 1 );
  ASSERT_LE( 3, errorCount() ) << "This file should contain at least 3 error";
  EXPECT_EQ( 3, errorCount() ) << "This file should contain 3 error";

  /**
   * We're expecting a WEBVTT_MALFORMED_TIMESTAMP error on the 3rd line.
   */
  expectEquals( getError( 0 ), WEBVTT_MALFORMED_TIMESTAMP, 3, 15 );
  /**
   * Expecting WEBVTT_EXPECTED_WHITESPACE at the 25th column of the 3rd line
   */
  expectEquals( getError( 1 ), WEBVTT_EXPECTED_WHITESPACE, 3, 25 );
  /**
   * Expecting WEBVTT_INVALID_CUESETTING at the 25th column of the 3rd line
   */
  expectEquals( getError( 2 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}
