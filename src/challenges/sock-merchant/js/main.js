const merchantUniques = {};
let totalMerchantPairs = 0;

function sockMerchant(n, ar) {
  for (var i = 0; i < n; i++) {
    if (merchantUniques.hasOwnProperty(ar[i])) {
      totalMerchantPairs++;
      delete merchantUniques[ar[i]];
    } else {
      merchantUniques[ar[i]] = 0;
    }
  }
  return totalMerchantPairs;
}

(main = () => {
  const n = 9;
  const ar = [10, 20, 20, 10, 10, 30, 50, 10, 20];
  const result = sockMerchant(n, ar);
})();
