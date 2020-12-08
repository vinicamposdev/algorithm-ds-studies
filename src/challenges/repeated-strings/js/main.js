function repeatedString(s, n) {
    let repeatedStrings = 0
    const totalNumberOfAs =  (s.match(/a/g) || []).length

    const majoritaryRepeationCases = Math.floor(n / s.length) * totalNumberOfAs

    const restRepeationCases = n % s.length 

    for(let i = 0; i < restRepeationCases; i++) {
        if(s[i] === 'a') {
            repeatedStrings++
        }
    }

    return repeatedStrings + majoritaryRepeationCases
}
  
(main = () => {
    const n = 10;
    const ar = 'aba';
    const output = 7
    if(repeatedString(ar, n) === output) {
        console.log(true)
    } else console.log(false)
})();
