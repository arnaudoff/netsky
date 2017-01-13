import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';

import { PacketDetailsModule } from './packet-details.module';

export function main() {
   describe('Packet details component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [PacketDetailsModule]
      });
    });

    it('should have a d3 partition',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let packetDetailsDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(packetDetailsDOMElement.querySelectorAll('ul').length)
              .toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<packet-details></packet-details>'
})
class TestComponent {}
