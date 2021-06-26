import { Pipe, PipeTransform } from '@angular/core';
import {Coffee} from "./coffee.model";

@Pipe({
  name: 'filter'
})
export class FilterPipe implements PipeTransform {
  transform(items: Coffee[], searchText: string): Coffee[] {
    if(!items) return [];
    if(!searchText) return [];
    searchText = searchText.toLowerCase()

    return items.filter(it => {
      return it.name.toLowerCase().includes(searchText) ||
        it.origin.toLowerCase().includes(searchText);

      // return it.name.toLowerCase().includes(searchText);
    })
  }
}
