function countingValleys(steps, path) {
  let height = 0;
  let count = 0;
  for (let i = 0; i < steps; i++) {
    if (path[i] == "U") height++;
    else {
      if (height == 0) count++;
      height--;
    }
  }
  if (height < 0) count--;

  return count;
}

(main = () => {
  const n = 8;
  const ar = ["U", "D", "D", "D", "U", "D", "U", "U"];
  countingValleys(n, ar);
})();
