describe('Capture', () => {

  beforeEach( () => {
    browser.get('/capture');
  });

  it('should have a packet list', () => {
    expect(element(by.css('capture packet-list')).isPresent()).toEqual(true);
  });

  it('should have packet details', () => {
    expect(element(by.css('capture packet-details')).isPresent()).toEqual(true);
  });

  it('should have packet bytes', () => {
    expect(element(by.css('capture packet-bytes')).isPresent()).toEqual(true);
  });

});
