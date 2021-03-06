#include <iostream>
#include "gtest/gtest.h"
#include "v8_test_fixture.h"
#include "v8.h"

using namespace v8;

class MaybeLocalTest : public V8TestFixture {
};

TEST_F(MaybeLocalTest, MaybeLocal) {
  Isolate::Scope isolate_scope(isolate_);
  const HandleScope handle_scope(isolate_);
  Handle<Context> context = Context::New(isolate_);
  Context::Scope context_scope(context);

  MaybeLocal<Value> m;
  EXPECT_TRUE(m.IsEmpty());
  ASSERT_DEATH(m.ToLocalChecked(), "Fatal error");

  Local<Number> nr = Number::New(isolate_, 18);
  MaybeLocal<Number> maybe_nr = MaybeLocal<Number>(nr);
  EXPECT_FALSE(maybe_nr.IsEmpty());

  Local<Number> nr2;
  // The following pattern can be nice to use with if statements
  // since ToLocal returns a bool if the MaybeLocal is empty.
  EXPECT_TRUE(maybe_nr.ToLocal<Number>(&nr2));
  EXPECT_TRUE(maybe_nr.ToLocal(&nr2));
  EXPECT_EQ(nr2->Value(), 18);

  // the {} will use the types, MaybeLocal default constructor so this would
  // be the same as writing MaybeLocal<Value> something = MaybeLocal<Value>();
  MaybeLocal<Value> something = {};
  std::cout << something.IsEmpty() << '\n';
  MaybeLocal<Value> something2 = MaybeLocal<Value>();
  std::cout << something2.IsEmpty() << '\n';
}
