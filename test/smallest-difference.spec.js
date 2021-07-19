const program = require('../src/challenges/smallest-difference/js');
const chai = require('chai');

it('Test Case #1', function () {
  chai.expect(program.smallestDifference([-1, 5, 10, 20, 28, 3], [26, 134, 135, 15, 17])).to.deep.equal([28, 26]);
});
