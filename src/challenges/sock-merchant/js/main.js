function sockMerchant(n, ar) {
  const merchantUniques = {};

  return ar.reduce((totalMerchantPairs, i) => {
    if (merchantUniques[i]) {
      delete merchantUniques[i];
      return totalMerchantPairs + 1;
    } else {
      merchantUniques[i] = true;
      return totalMerchantPairs;
    }
  }, 0);
}

(main = () => {
  const n = 9;
  const ar = [10, 20, 20, 10, 10, 30, 50, 10, 20];
  sockMerchant(n, ar);
})();
