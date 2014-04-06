## Server

#### UserAccounts
* userAccountID primary key
* username unique
* password --stored in the database (hashed)?
* blacklisted {false, true}
* whitelisted {true, false}

-------------------------

## Items

#### Notes
* These are static; they're immutable during runtime

#### GlobalItemList
* globalItemListID primary key
* itemName unique
* itemImage
* type {mundane, consumable, equipment, etc.}
* maxStackSize {1-max; -1 for false}
* maxUniqueCopies {1-max; -1 for unlimited}

#### MundaneItems
* mundaneItemID primary key
* globalItemListID foreign key -> GlobalItemList.globalItemListID
* TODO: attributes

#### Consumables
* consumableID primary key
* globalItemListID foreign key -> GlobalItemList.globalItemListID
* TODO: attributes

#### Equipment
* equipmentID primary key
* globalItemListID foreign key -> GlobalItemList.globalItemListID
* TODO: attributes

-------------------------

## Player

#### Notes
* These change as the character progresses and grows

#### PlayerCharacters
* characterID primary key
* name unique

#### Player Statistics
* currentLevel
* currentExperience
* maxHealth
* maxMana
* currentHealth
* currentMana
* attack
* defence
* etc.

#### Player Equipment
* weapon foreign key -> Equipment.equipmentID
* helmet foreign key -> Equipment.equipmentID
* armour foreign key -> Equipment.equipmentID
* TODO: etc.

#### PlayerInventoryItems
* characterID foreign key -> PlayerCharacter.characterID
* globalItemListID foreign key -> GlobalItemList.globalItemListID


-------------------------

#### TODO

* customizable sprite