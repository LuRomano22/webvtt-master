#include "cue_testfixture"
class CueSettingLine : public CueTest { };

/**
 * Test a two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigit)
{
  loadVtt( "cue-settings/line/many-digit.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 12345, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigitHighBoundary)
{
  loadVtt( "cue-settings/line/many-digit-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 32767, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *   6. Ignoring the trailing percent sign, if any, interpret value as a
 *      (potentially signed) integer, and let number be that number.
 *   8. Let cue's text track cue line position be number.
 *   9. If the last character in value is a U+0025 PERCENT SIGN character (%),
 *      then let cue's text track cue snap-to-lines flag be false. Otherwise, let
 *      it be true.
 */
TEST_F(CueSettingLine, ManyDigitLowBoundary)
{
  loadVtt( "cue-settings/line/many-digit-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigitNegative)
{
  loadVtt( "cue-settings/line/many-digit-negative.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( -12345, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigitNegativeHighBoundary)
{
  loadVtt( "cue-settings/line/many-digit-negative-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( -32767, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigitNegativeLowBoundary)
{
  loadVtt( "cue-settings/line/many-digit-negative-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigitPercentage)
{
  loadVtt( "cue-settings/line/many-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 55, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/line/many-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 100, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, ManyDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/line/many-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigit)
{
  loadVtt( "cue-settings/line/double-digit.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 54, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitHighBoundary)
{
  loadVtt( "cue-settings/line/double-digit-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 99, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitLowBoundary)
{
  loadVtt( "cue-settings/line/double-digit-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitNegative)
{
  loadVtt( "cue-settings/line/double-digit-negative.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( -54, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitNegativeHighBoundary)
{
  loadVtt( "cue-settings/line/double-digit-negative-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( -99, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative two digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitNegativeLowBoundary)
{
  loadVtt( "cue-settings/line/double-digit-negative-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitPercentage)
{
  loadVtt( "cue-settings/line/double-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 54, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/line/double-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 99, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a two digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, DoubleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/line/double-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a single digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigit)
{
  loadVtt( "cue-settings/line/single-digit.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 5, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a single digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitHighBoundary)
{
  loadVtt( "cue-settings/line/single-digit-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 9, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a single digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitLowBoundary)
{
  loadVtt( "cue-settings/line/single-digit-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative single digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitNegative)
{
  loadVtt( "cue-settings/line/single-digit-negative.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( -5, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative single digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitNegativeHighBoundary)
{
  loadVtt( "cue-settings/line/single-digit-negative-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( -9, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a negative single digit non-percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitNegativeLowBoundary)
{
  loadVtt( "cue-settings/line/single-digit-negative-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).lineNumber() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
}

/**
 * Test a single digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitPercentage)
{
  loadVtt( "cue-settings/line/single-digit-pct.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 5, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a single digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitPercentageHighBoundary)
{
  loadVtt( "cue-settings/line/single-digit-pct-high-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 9, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test a single digit percentage value for setting line.
 *
 * From http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * If name is a case-sensitive match for "line"
 *  6. Ignoring the trailing percent sign, if any, interpret value as a (potentially signed) integer, and let number be that number.
 * 8. Let cue's text track cue line position be number.
 * 9. If the last character in value is a U+0025 PERCENT SIGN character (%), then let cue's text track cue snap-to-lines flag be false. Otherwise, let it be true.
 */
TEST_F(CueSettingLine, SingleDigitPercentageLowBoundary)
{
  loadVtt( "cue-settings/line/single-digit-pct-low-boundary.vtt", 1 );
  ASSERT_EQ( 0, errorCount() ) << "This file should contain no errors.";
  ASSERT_EQ( 0, getCue( 0 ).relativeLinePositionPercentage() );
  ASSERT_FALSE( getCue( 0 ).snapToLines() );
}

/**
 * Test that the parser does not change line if the keyword matches nothing.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 *   If name is a case-sensitive match for "vertical" ...
 *   If name is a case-sensitive match for "line" ...
 *   If name is a case-sensitive match for "position" ...
 *   If name is a case-sensitive match for "size" ...
 *   If name is a case-sensitive match for "align" ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingLine, BadKeyword)
{
  loadVtt( "cue-settings/line/bad-keyword.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed setting should be skipped and "auto" and true are default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the
   * 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test that the parser does not allow a setting to start with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.  5. Next setting:
 *    Continue to the next token, if any.
 */
TEST_F(CueSettingLine, NoKeyword)
{
  loadVtt( "cue-settings/line/no-keyword.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed setting should be skipped and "auto" and true are default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd line
   * We could return a smarter error, after a little bit of refactoring, perhaps.
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.  5. Next setting:
 *    Continue to the next token, if any.
 */
TEST_F(CueSettingLine, NoDelimiter)
{
  loadVtt( "cue-settings/line/no-delimiter.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed setting should be skipped and "auto" and true are default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the
   * 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test that the parser requires a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if
 *    the first U+003A COLON character (:) in setting is either the first
 *    or last character of setting, then jump to the step labeled next
 *    setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingLine, BadDelimiter)
{
  loadVtt( "cue-settings/line/bad-delimiter.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because
   * the malformed setting should be skipped and "auto" and true are
   * default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );
  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th
   * column of the 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test what happens when the line value contains a character it should not.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *  1. If value contains any characters other than U+002D HYPHEN-MINUS
 *     characters (-), U+0025 PERCENT SIGN characters (%), and ASCII digits,
 *     then jump to the step labeled next setting.
 */
TEST_F(CueSettingLine, BadValue)
{
  loadVtt( "cue-settings/line/bad-value.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed setting should be skipped and "auto" and true are default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );

  /**
   * We're expecting a WEBVTT_LINE_BAD_VALUE error on the 25th column of the 3rd
   * line
   */
  expectEquals( getError( 0 ), WEBVTT_LINE_BAD_VALUE, 3, 25 );
}

/**
 * Test that the parser does not allow a setting to end with a colon.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.  5. Next setting:
 *    Continue to the next token, if any.
 */
TEST_F(CueSettingLine, NoValue)
{
  loadVtt( "cue-settings/line/no-value.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed setting should be skipped and "auto" and true are default.
   */
  expectDefaultLineSetting( getCue( 0 ) );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the 3rd
   * line
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test what happens when the line value contains a character it should not.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 *  1. If value contains any characters other than U+002D HYPHEN-MINUS
 *     characters (-), U+0025 PERCENT SIGN characters (%), and ASCII digits, then
 *     jump to the step labeled next setting.
 */
TEST_F(CueSettingLine, BadValueSuffix)
{
  loadVtt( "cue-settings/line/bad-value-suffix.vtt", 1 );
  ASSERT_LE( 1, errorCount() );
  EXPECT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed setting should be skipped and "auto" and true are default.
   */
  expectDefaultLineSetting( getCue( 0 ) );

  /**
   * Should expect a WEBVTT_LINE_BAD_VALUE at the 25th column of the 3rd line.
   */
  expectEquals( getError( 0 ), WEBVTT_LINE_BAD_VALUE, 3, 25 );
}

/**
 * Test that the parser requires a colon in each of the two settings.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last
 *    character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingLine, WhitespaceDelimiter)
{
  loadVtt( "cue-settings/line/bad-whitespace-delimiter.vtt", 1 );
  ASSERT_LE( 2, errorCount() );
  EXPECT_EQ( 2, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed setting should be skipped and "auto" and true are default.
   */
  expectDefaultLineSetting( getCue( 0 ) );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of
   * the 3rd line, and a WEBVTT_INVALID_CUESETTING on the 30th column
   * of the 3rd line.
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
  expectEquals( getError( 1 ), WEBVTT_INVALID_CUESETTING, 3, 30 );
}

/**
 * Test that the parser does not allow a setting to start with a colon
 * and that it requires a colon in the other setting.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last
 *    character of setting, then jump to the step labeled next setting.
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingLine, BadWhitespaceBeforeDelimiter)
{
  loadVtt( "cue-settings/line/bad-whitespace-before-delimiter.vtt", 1 );
  ASSERT_LE( 2, errorCount() );
  EXPECT_EQ( 2, errorCount() );

  /**
   * line:68% -- snapToLines==false, linePositionPercentage==68
   */
  expectDefaultLineSetting( getCue( 0 ) );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of
   * the 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
  expectEquals( getError( 1 ), WEBVTT_INVALID_CUESETTING, 3, 30 );
}

/**
 * Test that the parser does not allow a setting to end with a colon
 * and that it requires a colon in the other setting.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 1. If setting does not contain a U+003A COLON character (:), or if the first
 *    U+003A COLON character (:) in setting is either the first or last character
 *    of setting, then jump to the step labeled next setting.  5. Next setting:
 *    Continue to the next token, if any.
 */
TEST_F(CueSettingLine, BadWhitespaceAfterDelimiter)
{
  loadVtt( "cue-settings/line/bad-whitespace-after-delimiter.vtt", 1 );
  ASSERT_LE( 2, errorCount() );
  EXPECT_EQ( 2, errorCount() );

  expectDefaultLineSetting( getCue( 0 ) );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of
   * the 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
  expectEquals( getError( 1 ), WEBVTT_INVALID_CUESETTING, 3, 31 );
}

/**
 * Test that the keyword is case-sensitive.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/27/2012):
 * 4. Run the appropriate substeps that apply for the value of name, as follows:
 * If name is a case-sensitive match for "vertical" ...
 * If name is a case-sensitive match for "line" ...
 * If name is a case-sensitive match for "position" ...
 * If name is a case-sensitive match for "size" ...
 * If name is a case-sensitive match for "align" ...
 * 5. Next setting: Continue to the next token, if any.
 */
TEST_F(CueSettingLine, UppercaseKeyword)
{
  loadVtt( "cue-settings/line/uppercase-keyword.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );
  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed settinga should be skipped and "auto" and true are default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );

  /**
   * We're expecting a WEBVTT_INVALID_CUESETTING error on the 25th column of the
   * 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_INVALID_CUESETTING, 3, 25 );
}

/**
 * Test that negative values are not allowed.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "line"
 *  7. If the last character in value is a U+0025 PERCENT SIGN character (%),
 *     but number is not in the range 0 = number = 100, then jump to the step
 *     labeled next setting.
 */
TEST_F(CueSettingLine, PercentNegative)
{
  loadVtt( "cue-settings/line/bad-pct-negative.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );

  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed settinga should be skipped and "auto" and true are default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );

  /**
   * We're expecting a WEBVTT_LINE_BAD_VALUE error on the 25th column
   * of the 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_LINE_BAD_VALUE, 3, 25 );
}

/**
 * Test that values over 100 are not allowed.
 *
 * http://dev.w3.org/html5/webvtt/#parse-the-webvtt-settings (11/28/2012):
 * If name is a case-sensitive match for "line"
 *  7. If the last character in value is a U+0025 PERCENT SIGN character (%),
 *     but number is not in the range 0 = number = 100, then jump to the step
 *     labeled next setting.
 */
TEST_F(CueSettingLine, PercentOver100)
{
  loadVtt( "cue-settings/line/bad-pct-over-100.vtt", 1 );
  ASSERT_EQ( 1, errorCount() );
  /**
   * Line should be "auto" and snap-to-lines should be true because the
   * malformed settinga should be skipped and "auto" and true are default.
   */
  ASSERT_TRUE( getCue( 0 ).isLinePositionAuto() );
  ASSERT_TRUE( getCue( 0 ).snapToLines() );

  /**
   * We're expecting a WEBVTT_LINE_BAD_VALUE error on the 25th column of the 3rd line
   */
  expectEquals( getError( 0 ), WEBVTT_LINE_BAD_VALUE, 3, 25 );
}
