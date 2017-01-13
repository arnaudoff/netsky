describe('Filter step', () => {

  beforeEach(async () => {
    return await browser.get('/home/filter');
  });

  it('should have an input', () => {
    expect(element(by.css('input')).isPresent()).toEqual(true);
  });

});
