import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { StartStepComponent } from './start-step.module';

export function main() {
   describe('Start step component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [StartStepModule]
      });
    });

    it('should have a button',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let startStepDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(startStepDOMElement.querySelectorAll('button').length).toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<start-step></start-step>'
})

class TestComponent {}
