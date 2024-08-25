const MyContract = artifacts.require("MyContract");

contract("MyContract", accounts => {
  it("should correctly set and get the value", async () => {
    const instance = await MyContract.deployed();
    await instance.setValue(42);
    const value = await instance.value();
    assert.equal(value.toNumber(), 42, "The value should be 42");
  });
});
