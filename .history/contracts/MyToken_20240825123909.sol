// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;
RC20/ERC20.sol";
Ownable.sol";
contract MyToken is ERC20, Ownable {
    constructor(uint256 initialSupply) ERC20("MyToken", "MTK") {
        _mint(msg.sender, initialSupply);
    }

    function mint(address to, uint256 amount) public onlyOwner {
        _mint(to, amount);
    }
}
