import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { CaptureModule } from './capture.module';

export function main() {
   describe('Capture component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [CaptureModule]
      });
    });

    it('should work',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let captureDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(captureDOMElement.querySelectorAll('packet-list').length).toEqual(1);
            expect(captureDOMElement.querySelectorAll('packet-details').length).toEqual(1);
            expect(captureDOMElement.querySelectorAll('packet-bytes').length).toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<capture></capture>'
})

class TestComponent {}
