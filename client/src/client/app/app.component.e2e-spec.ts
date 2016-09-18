describe('App', () => {

  beforeEach( () => {
    browser.get('/');
  });

  it('should have a title', () => {
    expect(browser.getTitle()).toEqual('Netsky');
  });

  it('should have <nav>', () => {
    expect(element(by.css('app navbar nav')).isPresent()).toEqual(true);
  });

  it('should have correct nav text for Home', () => {
    expect(element(by.css('app navbar nav a:first-child')).getText()).toEqual('HOME');
  });

});
