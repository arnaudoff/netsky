describe('Start step', () => {

  beforeEach(() => {
    browser.get('/home/start');
  });

  it('should have a start button', () => {
    expect(element(by.css('button')).isPresent()).toEqual(true);
  });

});
