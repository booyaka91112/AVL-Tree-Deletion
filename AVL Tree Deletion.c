static Node rightRotate( Node K2 ) {
	Node K1;
	K1 = K2.Left;
	K2.Left = K1.Right;
	K1.Right = K2;
	K2.Height = Max( Height( K2.Left ), Height( K2.Right ) ) + 1;
	K1.Height = Max( Height( K1.Left ), K2.Height ) + 1;
	return K1;
}
static Node leftRotate( Node K1 ) {
	Node K2;
	K2 = K1.Right;
	K1.Right = K2.Left;
	K2.Left = K1;
	K1.Height = Max( Height( K1.Left ), Height( K1.Right ) ) + 1;
	K2.Height = Max( Height( K2.Right ), K1.Height ) + 1;
	return K2;
}

static Node remove(Node node, K key) {

	Node retNode;
	if( key < node.key ) {
		node.left = remove(node.left , key); //繼續往左尋找
		// return node;
		retNode = node;
	} else if(key > node.key ) {
		node.right = remove(node.right, key); //繼續往右尋找
		retNode = node;
	} else { // key == node.key

		// 待刪除節點左子樹為空的情況
		if(node.left == null) {
			Node rightNode = node.right;
			node.right = null;
			// return rightNode;
			retNode = rightNode;
		}

		// 待刪除節點右子樹為空的情況
		else if(node.right == null) {
			Node leftNode = node.left;
			node.left = null;
			retNode = leftNode;
		}

		// 待刪除節點左右子樹均不為空的情況
		else {
			// 找到比待刪除節點大的最小節點, 即待刪除節點右子樹的最小節點(BST做法) 
			// 用這個節點頂替待刪除節點的位置
			Node successor = minimum(node.right);
			successor.right = remove(node.right, successor.key);
			successor.left = node.left;
			node.left = null;
			node.right = null;
			// return successor;
			retNode = successor;
		}
	}

	// 更新height
	retNode.height = 1 + Math.max(getHeight(retNode.left), getHeight(retNode.right));

	// 平衡因子
	int balanceFactor = getBalanceFactor(retNode);

	// 平衡維護
	// LL
	if (balanceFactor > 1 && getBalanceFactor(retNode.left) >= 0)
		return rightRotate(retNode);

	// RR
	if (balanceFactor < -1 && getBalanceFactor(retNode.right) <= 0)
		return leftRotate(retNode);

	// LR
	if (balanceFactor > 1 && getBalanceFactor(retNode.left) < 0) {
		retNode.left = leftRotate(retNode.left);
		return rightRotate(retNode);
	}

	// RL
	if (balanceFactor < -1 && getBalanceFactor(retNode.right) > 0) {
		retNode.right = rightRotate(retNode.right);
		return leftRotate(retNode);
	}
	return retNode;
}
