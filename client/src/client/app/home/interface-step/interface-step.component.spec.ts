import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { InterfaceStepComponent } from './interface-step.module';

export function main() {
   describe('Interface step component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [InterfaceStepComponent]
      });
    });

    it('should have a dropdown',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let interfaceStepDOMElement = fixture.debugElement.children[0].nativeElement;

            expect(interfaceStepDOMElement.querySelectorAll('.dropdown').length).toEqual(1);
          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<interface-step></interface-step>'
})

class TestComponent {}
