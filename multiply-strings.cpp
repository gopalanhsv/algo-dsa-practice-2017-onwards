class Solution {
public:
    string
    multiply(string num1, string num2) {
        // Certain base cases of multiply by 0 and 1 covered
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        if (num1 == "1") {
            return num2;
        }
        if (num2 == "1") {
            return num1;
        }
        
        // Always go through each digit of smaller number and
        // multiply the digits by bigger number to improve speed
        // Reduces function calls
        if (num1.size() > num2.size()) {
            swap(num1, num2);
        }
        
        string partialProdSum = "0";
        int nZeroAtPartialProdEnd = 0;
        // Compute partial products and sum up the partial products
        // Compute a partial product by taking each digit char
        // in num1 and multiplying it with all chars in num2 and
        // padding it with the required number of zeroes
        for (int i = num1.size() - 1; i >= 0; --i) {
            auto & e1 = num1[i];
            // Partial product
            string currProduct = multiply(num2, int(e1 - '0'));
            // Pad partial product with apropriate
            // number of zeros at LSB
            currProduct += string(nZeroAtPartialProdEnd++, '0');
            // Add current partial product to partial products
            // sum computed uptill now
            partialProdSum = add(partialProdSum, currProduct);
        }
        
        return partialProdSum;
    }
    
private:
    
    string
    multiply(string& a, int b) {
        // Base cases to improve speed
        if (0 == b) {
            return "0";
        }
        if (1 == b) {
            return a;
        }
        
        // Multiply digits in 'a' from least significant to most
        // significant digit with 'b'. Multiply the digits of the numbers
        // from end to front
        int carry = 0;
        int i = a.size() - 1;
        string prodStr;
        int x = 0;
        while (carry > 0 || i >= 0) {
            // Multiplying any valid digits in string a with b and
            // adding result to carry
            if (i >= 0) {
                carry += int(a[i--] - '0') * b;
            }
            
            // Store the least significant digit to product
            // string and carry over the rest
            prodStr += char('0' + carry % 10);
            carry = carry / 10;
        }
        
        // Reverse product string
        reverse(prodStr.begin(), prodStr.end());
        return prodStr;
    }
    
    string
    add(string& a, string& b) {
        if ("0" == a) {
            return b;
        }
        if ("0" == b) {
            return a;
        }
        // Add from least significant to most significant digit.
        // So add the digits of the numbers from end to front
        int carry = 0;
        int i = a.size() - 1;
        int j = b.size() - 1;
        string sumStr;
        int x = 0;
        while (carry > 0 || i >= 0 || j >= 0) {
            // Adding any valid digits in strings a/b to carry
            if (i >= 0) {
                carry += int(a[i--] - '0'); 
            }
            if (j >= 0) {
                carry += int(b[j--] - '0'); 
            }

            // Store the least significant digit and carry over the rest
            sumStr += char('0' + carry % 10);
            carry /= 10;
        }
        
        // Reverse sum string
        reverse(sumStr.begin(), sumStr.end());
        return sumStr;
    }
    
};
