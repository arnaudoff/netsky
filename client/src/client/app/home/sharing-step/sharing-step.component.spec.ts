import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { SharingStepComponent } from './sharing-step.module';

export function main() {
   describe('Sharing step component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [SharingStepModule]
      });
    });

    it('should have an actual list',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let sharingStepDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(sharingStepDOMElement.querySelectorAll('div.list').length).toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<sharing-step></sharing-step>'
})

class TestComponent {}
