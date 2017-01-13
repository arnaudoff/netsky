describe('Interface step', () => {

  beforeEach(async () => {
    return await browser.get('/home/interface');
  });

  it('should have a dropdown', () => {
    expect(element(by.css('div dropdown')).isPresent()).toEqual(true);
  });

});
