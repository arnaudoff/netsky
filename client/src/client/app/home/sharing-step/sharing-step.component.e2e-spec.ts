describe('Sharing step', () => {

  beforeEach(() => {
    browser.get('/home/sharing');
  });

  it('should have a list', () => {
    expect(element(by.css('div.list')).isPresent()).toEqual(true);
  });

});
