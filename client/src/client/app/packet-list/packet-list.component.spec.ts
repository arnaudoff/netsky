import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { PacketListComponent } from './packet-list.module';

export function main() {
   describe('Packet list component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [PacketListModule]
      });
    });

    it('should have an actual list',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let packetListDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(packetListDOMElement.querySelectorAll('ul').length).toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<packet-list></packet-list>'
})

class TestComponent {}
