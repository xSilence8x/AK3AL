/*!
 * \file       tests.cpp
 * \author     Sevcik, Jurena
 * \date       15. 2. 2022
 * \brief      Unit tests for DTMF module.
 * ******************************************
 * \attention
 * &copy; Copyright (c) 2022 FAI UTB. All rights reserved.
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/* Includes --------------------------------------------------------------------------------------*/

#include "gmock/gmock.h"

#include "gtest/gtest.h"
#include <limits>
#include <vector>

extern "C" {
#include "dtmf.h"
#include "vector.h"
#include "wavfile.h"
}
/* Private types ---------------------------------------------------------------------------------*/

class DTMFTest : public ::testing::Test
{
  // Test interface
protected:
  virtual void SetUp() override { mVector = Vector_Create(1024, 1024); }
  virtual void TearDown() override { Vector_Destroy(&mVector); }
  Vector_t *mVector;
};

class DTMFTestParam :
  public DTMFTest,
  public ::testing::WithParamInterface<std::tuple<char, std::vector<short>>>
{
};

/* Private function definitions ------------------------------------------------------------------*/
template <typename T, T... ints>
void loadSamples(Vector_t *container,
                 std::vector<short> &samples,
                 std::integer_sequence<T, ints...> int_seq)
{
  (void)int_seq;
  short data;
  ((Vector_At(container, ints, &data), samples.push_back(data)), ...);
}

TEST_P(DTMFTestParam, generate)
{
  auto [symbol, expected] = GetParam();
  DTMF_Generate(mVector, symbol);
  // clang-format off
  auto indexes = std::integer_sequence<std::size_t, 10, 100, 1000, 1250, 1450, 2250, 2750, 3250, 4250, 5250, 6250, 7250>{};
  // clang-format on
  std::vector<short> samples;
  loadSamples(mVector, samples, indexes);
  ASSERT_THAT(samples, expected);
  ASSERT_EQ(Vector_Length(mVector), 8000);
}

INSTANTIATE_TEST_SUITE_P(
  generate,
  DTMFTestParam,
  testing::Values(
    std::make_tuple('1',
                    std::vector<short>{
                      -794, -322, 1414, -1111, 1606, 390, -1111, 1662, 1961, 1111, -390, -1662}),
    std::make_tuple('2',
                    std::vector<short>{
                      -1599, -1923, 707, -1555, 1681, -804, 444, -168, -19, -444, -1195, -1831}),
    std::make_tuple('3',
                    std::vector<short>{
                      -1546, -738, 0, -1536, -89, 750, -1536, 1026, 149, 1536, -750, -1026}),
    std::make_tuple('4',
                    std::vector<short>{
                      -304, -57, 1707, 368, 351, -187, -1479, -92, 1363, 1479, -577, -1755}),
    std::make_tuple('5',
                    std::vector<short>{
                      -1109, -1658, 1000, -76, 426, -1382, 76, -1923, -617, -76, -1382, -1923}),
    std::make_tuple('6',
                    std::vector<short>{
                      -1056, -473, 292, -56, -1345, 172, -1904, -728, -448, 1904, -938, -1118}),
    std::make_tuple(
      '7', std::vector<short>{326, -159, 707, 151, 1188, -512, -1262, 1538, 273, 1262, -902, -124}),
    std::make_tuple('8',
                    std::vector<short>{
                      -479, -1760, 0, -292, 1263, -1707, 292, -292, -1707, -292, -1707, -292}),
    std::make_tuple('9',
                    std::vector<short>{
                      -425, -575, -707, -273, -508, -151, -1687, 902, -1538, 1687, -1262, 512}),
    std::make_tuple('0',
                    std::vector<short>{
                      18, -1947, -707, -804, 462, -1831, 1195, -19, -1555, -1195, -168, -1980}),
    std::make_tuple('A',
                    std::vector<short>{
                      -467, -449, 1414, 275, 754, 1175, 275, 1387, 785, -275, -1175, -1387}),
    std::make_tuple(
      'B', std::vector<short>{22, -184, 1707, 1755, -500, 598, -92, -368, 187, 92, -1363, -1479}),
    std::make_tuple(
      'C', std::vector<short>{653, -286, 707, 1538, 336, 273, 124, 1262, -902, -124, -1687, 151}),
    std::make_tuple('D',
                    std::vector<short>{
                      1150, -474, 0, 1026, -463, 149, 1026, 1536, -750, -1026, -149, -1536}),
    std::make_tuple(
      '*', std::vector<short>{823, -347, 0, -360, 388, -636, -360, 1812, 425, 360, 636, -1812}),
    std::make_tuple('#',
                    std::vector<short>{
                      71, -763, -1414, -785, -1308, -275, -785, 1175, -1387, 785, 275, -1175}),
    std::make_tuple(' ', std::vector<short>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
    std::make_tuple('a',
                    std::vector<short>{
                      -467, -449, 1414, 275, 754, 1175, 275, 1387, 785, -275, -1175, -1387}),
    std::make_tuple(
      'b', std::vector<short>{22, -184, 1707, 1755, -500, 598, -92, -368, 187, 92, -1363, -1479}),
    std::make_tuple(
      'c', std::vector<short>{653, -286, 707, 1538, 336, 273, 124, 1262, -902, -124, -1687, 151}),
    std::make_tuple('d',
                    std::vector<short>{
                      1150, -474, 0, 1026, -463, 149, 1026, 1536, -750, -1026, -149, -1536})));

TEST(dtmf, generate_null)
{
  DTMF_Generate(nullptr, '3');
}

TEST_P(DTMFTestParam, generateSanitizeSymbols)
{
  auto [symbol, expectedResult] = GetParam();
  ASSERT_TRUE(DTMF_Generate(mVector, symbol));
}

TEST_F(DTMFTest, generateReturnsFalseOnInvalidSymbol)
{
  std::string invalidSymbols{"eEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ"};
  for (auto it = invalidSymbols.begin(); it != invalidSymbols.end(); ++it) {
    ASSERT_FALSE(DTMF_Generate(mVector, *it))
      << "The symbol '" << *it << "' shall be considered as invalid.";
  }
}