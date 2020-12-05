function sockMerchant(n, ar, matchingPairs = 0) {
  if (n === 0) {
    return matchingPairs;
  }
  const isMatchingPair = ar[n - 1] === ar[n - 2];
  if (isMatchingPair) {
    ar.pop();
  }
  ar.pop();

  return sockMerchant(ar.length, ar, matchingPairs + isMatchingPair);
}

(main = () => {
  const n = 9;
  const ar = [10, 20, 20, 10, 10, 30, 50, 10, 20];
  const result = sockMerchant(n, ar.sort());
  console.log(result);
})();
