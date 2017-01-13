describe('Start step', () => {

  beforeEach(async () => {
    return await browser.get('/home/start');
  });

  it('should have a start button', () => {
    expect(element(by.css('button')).isPresent()).toEqual(true);
  });

});
