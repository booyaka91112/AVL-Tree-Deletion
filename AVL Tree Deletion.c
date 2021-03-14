	// 對節點y進行向右旋轉操作，返回旋轉後新的根節點x
    //        y                              x
    //       / \                           /   \
    //      x   T4     向右旋轉 (y)        z     y
    //     / \       - - - - - - - ->    / \   / \
    //    z   T3                       T1  T2 T3 T4
    //   / \
    // T1   T2
    private Node rightRotate(Node y) {
        Node x = y.left;
        Node T3 = x.right;

        // 向右旋轉過程
        x.right = y;
        y.left = T3;

        // 更新height
        y.height = max(getHeight(y.left), getHeight(y.right)) + 1;
        x.height = max(getHeight(x.left), getHeight(x.right)) + 1;

        return x;
    }

    // 對節點y進行向左旋轉操作，返回旋轉後新的根節點x
    //    y                             x
    //  /  \                          /   \
    // T1   x     向左旋轉 (y)       y     z
    //     / \   - - - - - - - ->   / \   / \
    //   T2  z                     T1 T2 T3 T4
    //      / \
    //     T3 T4
    private Node leftRotate(Node y) {
        Node x = y.right;
        Node T2 = x.left;

        // 向左旋轉過程
        x.left = y;
        y.right = T2;

        // 更新height
        y.height = max(getHeight(y.left), getHeight(y.right)) + 1;
        x.height = max(getHeight(x.left), getHeight(x.right)) + 1;

        return x;
    }

    private Node remove(Node node, K key){

        Node retNode;
        if( key < node.key ){
            node.left = remove(node.left , key); //繼續往左尋找
            // return node;
            retNode = node;
        }
        else if(key > node.key ){
            node.right = remove(node.right, key); //繼續往右尋找
            // return node;
            retNode = node;
        }
        else{   // key == node.key

            // 待刪除節點左子樹為空的情況
            if(node.left == null){
                Node rightNode = node.right;
                node.right = null;
                // return rightNode;
                retNode = rightNode;
            }

            // 待刪除節點右子樹為空的情況
            else if(node.right == null){
                Node leftNode = node.left;
                node.left = null;
                // return leftNode;
                retNode = leftNode;
            }

            // 待刪除節點左右子樹均不為空的情況
            else{
                // 找到比待刪除節點大的最小節點, 即待刪除節點右子樹的最小節點
                // 用這個節點頂替待刪除節點的位置
                Node successor = minimum(node.right);
                //successor.right = removeMin(node.right);
                successor.right = remove(node.right, successor.key);
                successor.left = node.left;

                node.left = node.right = null;
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

