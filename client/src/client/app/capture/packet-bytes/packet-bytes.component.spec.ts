import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';

import { PacketBytesModule } from './packet-bytes.module';

export function main() {
   describe('Packet bytes component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [PacketBytesModule]
      });
    });

    it('should have something',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let packetBytesDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(packetBytesDOMElement.querySelectorAll('ul').length)
              .toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<packet-bytes></packet-bytes>'
})
class TestComponent {}
