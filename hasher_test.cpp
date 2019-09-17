#include "chasher.h"
#include "gtest/gtest.h"

namespace 
{
	TEST(my_hasher, spawn)
	{
		void *ctx;

		ctx = hasher_create();
		EXPECT_TRUE(ctx);
	}
	TEST(my_hasher, eventfd)
	{
		void *ctx;

		ctx = hasher_create();
		EXPECT_TRUE(hasher_getfd(ctx) > 1);
	}
	TEST(my_hasher, hash_result_wo_update)
	{
		void *ctx;

		ctx = hasher_create();
		EXPECT_EQ(strcmp(hasher_result(ctx), "d41d8cd98f00b204e9800998ecf8427e"), 0);
		hasher_destroy(ctx);
	}
	TEST(my_hasher, hash_result_empty_update)
	{
		void *ctx;

		ctx = hasher_create();
		hasher_update(ctx, "", strlen(""));
		EXPECT_EQ(strcmp(hasher_result(ctx), "d41d8cd98f00b204e9800998ecf8427e"), 0);
		hasher_destroy(ctx);
	}
	TEST(my_hasher, hash_single_update)
	{
		void *ctx;

		ctx = hasher_create();
		hasher_update(ctx, "Henlo", strlen("Henlo"));
		hasher_update(ctx, "", strlen(""));
		EXPECT_EQ(strcmp(hasher_result(ctx), "cc85df3726ae3cd688fd0c770871d690"), 0);
		hasher_destroy(ctx);
	}

	TEST(my_hasher, hash_two_update)
	{
		void *ctx;

		ctx = hasher_create();
		hasher_update(ctx, "Henlo", strlen("Henlo"));
		hasher_update(ctx, "Henlo", strlen("Henlo"));
		hasher_update(ctx, "", strlen(""));
		EXPECT_EQ(strcmp(hasher_result(ctx), "7f2cb9da38fdb53a2c1cca1b60089314"), 0);
		hasher_destroy(ctx);
	}

		TEST(my_hasher, hash_single_update_wo_end)
	{
		void *ctx;

		ctx = hasher_create();
		hasher_update(ctx, "Henlo", strlen("Henlo"));
		EXPECT_EQ(strcmp(hasher_result(ctx), "cc85df3726ae3cd688fd0c770871d690"), 0);
		hasher_destroy(ctx);
	}

	TEST(my_hasher, hash_two_update_wo_end)
	{
		void *ctx;

		ctx = hasher_create();
		hasher_update(ctx, "Henlo", strlen("Henlo"));
		hasher_update(ctx, "Henlo", strlen("Henlo"));
		EXPECT_EQ(strcmp(hasher_result(ctx), "7f2cb9da38fdb53a2c1cca1b60089314"), 0);
		hasher_destroy(ctx);
	}

	TEST(my_hasher, hash_thousands_update_wo_end)
	{
		void *ctx;

		ctx = hasher_create();
		for (int i = 0; i < 25380; ++i)
		{
			hasher_update(ctx, "H", strlen("H"));
		}
		EXPECT_EQ(strcmp(hasher_result(ctx), "5ba9fcfe5a4b35b37bbe375441815ee4"), 0);
		hasher_destroy(ctx);
	}
	TEST(my_hasher, hash_thousands_update_wo_end_inverted)
	{
		void *ctx;

		ctx = hasher_create();
		for (int i = 0; i < 25381; ++i)
		{
			hasher_update(ctx, "H", strlen("H"));
		}
		EXPECT_TRUE(strcmp(hasher_result(ctx), "5ba9fcfe5a4b35b37bbe375441815ee4") != 0);
		hasher_destroy(ctx);
	}
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}