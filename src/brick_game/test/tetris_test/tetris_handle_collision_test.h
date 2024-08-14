#ifndef CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_TETRIS_TEST_TETRIS_HANDLE_COLLISION_TEST_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_TEST_BACK_TEST_TETRIS_TEST_TETRIS_HANDLE_COLLISION_TEST_H_

#include "tetris_test.h"

class TetrisHandleCollisionTest : public ::testing::Test
{
};

TEST_F(TetrisHandleCollisionTest, case_1)
{
    int col = TetrisHandleCollision(COLLIDE_WITH_BORDER, kDirLeft);
    ASSERT_EQ(col, COL_STATE_COL);
}

TEST_F(TetrisHandleCollisionTest, case_2)
{
    int col = TetrisHandleCollision(COLLIDE_WITH_BORDER, kDirRight);
    ASSERT_EQ(col, COL_STATE_COL);
}

TEST_F(TetrisHandleCollisionTest, case_3)
{
    int col = TetrisHandleCollision(COL_STATE_COL, kDirLeft);
    ASSERT_EQ(col, COL_STATE_COL);
}

TEST_F(TetrisHandleCollisionTest, case_4)
{
    int col = TetrisHandleCollision(COLLIDE_WITH_BORDER, kDirDown);
    ASSERT_EQ(col, COL_STATE_CRIT);
}

TEST_F(TetrisHandleCollisionTest, case_5)
{
    int col = TetrisHandleCollision(COL_STATE_COL, kDirDown);
    ASSERT_EQ(col, COL_STATE_CRIT);
}

#endif