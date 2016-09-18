describe('Packet list', () => {

  beforeEach(() => {
    browser.get('/capture');
  });

  it('should have a list', () => {
    expect(element(by.css('packet-list ul')).isPresent()).toEqual(true);
  });

});
