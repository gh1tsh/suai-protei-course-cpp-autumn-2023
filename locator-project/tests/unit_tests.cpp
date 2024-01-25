#include <gtest/gtest.h>

#include "locator.h"

#include <gtest/gtest.h>

class LocatorTest : public ::testing::Test {
protected:
	static Locator *locator;

	// Set up once before running all the test cases
	static void SetUpTestCase() {
		// Perform initialization, load data from a file, etc.
		locator = new Locator();
		locator->load_locator_config();
		locator->add_zone_trigger("zone_0_trigger", 0, "+71111111111", Event::ENTERING_EXITING_ZONE);
		locator->load_subscriber_data_from_file("/home/ghitsh/suai/suai-protei-course-cpp/data/subs_data.json");
		locator->add_proximity_trigger("test", "+73333333333", "+74444444444", 5);
	}

	// Tear down after all tests are completed
	static void TearDownTestCase() {
		// Clean up after all tests
		delete locator;
		locator = nullptr;
	}
};

Locator* LocatorTest::locator = nullptr; // Initialize the static member


TEST_F(LocatorTest, GetNonExistentZonePtr)
{
	auto z = locator->get_zone_ptr(999);
	EXPECT_EQ(z, nullptr);
}

TEST_F(LocatorTest, GetExistentZonePtr)
{
	auto z = locator->get_zone_ptr(0);
	EXPECT_EQ("zone_0", z->get_name());
}

TEST_F(LocatorTest, GetNonExistentZone)
{
	EXPECT_THROW(locator->get_zone(999), std::invalid_argument);
}

TEST_F(LocatorTest, GetExistentZone)
{
	Zone const& z = locator->get_zone(1);
	EXPECT_EQ("zone_1", z.get_name());
}

TEST_F(LocatorTest, GetNonExistentSubscriberData)
{
	EXPECT_THROW(
		locator->get_subscriber("88005553535"),
		std::invalid_argument
	);
}

TEST_F(LocatorTest, GetExistentSubscriberData)
{
	Subscriber const& s = locator->get_subscriber("+74444444444");
	EXPECT_EQ(s.get_x(), 6);
	EXPECT_EQ(s.get_y(), 7);
}

TEST_F(LocatorTest, ChangingSubscriberLocation)
{
	locator->set_subscriber_location("+71111111111", 10, 10);
	locator->set_subscriber_location("+71111111111", -10, -20);

	Subscriber const& s = locator->get_subscriber("+71111111111");
	EXPECT_EQ(s.get_x(), -10);
	EXPECT_EQ(s.get_y(), -20);
}

TEST_F(LocatorTest, SubscriberInZoneCheck)
{
	locator->add_zone(777, "test_zone", 50, 50, 20);
	locator->add_subscriber("+79115555555", 42, 42);
	std::list<Subscriber> subscribers_in_zone_777 = locator->get_subscribers_in_zone(777);

	EXPECT_EQ(subscribers_in_zone_777.size(), 1);
	EXPECT_EQ(subscribers_in_zone_777.begin()->get_id(), "+79115555555");
}

TEST_F(LocatorTest, SubscriberNotInZoneCheck)
{
	locator->add_subscriber("+79115555555", -81, -27);
	std::list<Subscriber> subscribers_in_zone_777 = locator->get_subscribers_in_zone(777);
	EXPECT_EQ(subscribers_in_zone_777.size(), 1);

}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
