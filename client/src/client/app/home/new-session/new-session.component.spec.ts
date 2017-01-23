import { Component } from '@angular/core';
import { async, TestBed } from '@angular/core/testing';
import { NewSessionModule } from './new-session.module';

export function main() {
   describe('New session component', () => {

    beforeEach(() => {
      TestBed.configureTestingModule({
        declarations: [TestComponent],
        imports: [NewSessionModule]
      });
    });

    it('should have text describing that interface should be chosen',
      async(() => {
        TestBed
          .compileComponents()
          .then(() => {
            let fixture = TestBed.createComponent(TestComponent);
            let newSessionDOMElement =
              fixture.debugElement.children[0].nativeElement;

            expect(
              newSessionDOMElement.querySelectorAll('.title')[0].textContent)
              .toEqual('Interface');

            expect(
              newSessionDOMElement.querySelectorAll('.title')[1].textContent)
              .toEqual('Filters');

            expect(
              newSessionDOMElement.querySelectorAll('.title')[2].textContent)
              .toEqual('Start the capture');

          });
        }));
    });
}

@Component({
  selector: 'test-cmp',
  template: '<new-session></new-session>'
})
class TestComponent {}
