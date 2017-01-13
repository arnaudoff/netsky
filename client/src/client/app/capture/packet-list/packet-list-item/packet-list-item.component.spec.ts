import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';

import { PacketListItemModule } from './packet-list-item.module';

export function main() {
   describe('Packet list item component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [PacketListItemModule]
      });
    });

    it('should have something',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let packetListItemDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(packetListItemDOMElement.querySelectorAll('div').length).toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<packet-list-item></packet-list-item>'
})
class TestComponent {}
